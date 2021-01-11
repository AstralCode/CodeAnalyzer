#include "VariableRulesModule.h"

#include "HeaderFile.h"
#include "SourceFile.h"
#include "StringHelper.h"

const CVariableRulesModule::VariableNameRuleArray CVariableRulesModule::m_aoVariableNameRules =
{
    CVariableRulesModule::SVariableNameRule{ "char", "c" },
    CVariableRulesModule::SVariableNameRule{ "bool", "b" },
    CVariableRulesModule::SVariableNameRule{ "BOOL", "b" },
    CVariableRulesModule::SVariableNameRule{ "int", "i" },
    CVariableRulesModule::SVariableNameRule{ "WORD", "w" },
    CVariableRulesModule::SVariableNameRule{ "DWORD", "dw" },
    CVariableRulesModule::SVariableNameRule{ "short", "s" },
    CVariableRulesModule::SVariableNameRule{ "long", "l" },
    CVariableRulesModule::SVariableNameRule{ "long long", "ll" },
    CVariableRulesModule::SVariableNameRule{ "float", "f" },
    CVariableRulesModule::SVariableNameRule{ "double", "d" },
    CVariableRulesModule::SVariableNameRule{ "long double", "ld" }
};

// ^^x
// void CVariableRulesModule::OnPreExecute
// 3BGO NTP-1 25-10-2020
void CVariableRulesModule::OnPreExecute()
{
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eVariableIncorrectNameCount, "Incorrect Variable Names" );
}

// ^^x
// void CVariableRulesModule::ProcessHeaderFile
// 3BGO NTP-1 25-10-2020
void CVariableRulesModule::ProcessHeaderFile( const CHeaderFile& oHeaderFile )
{
    ValidateVariables( oHeaderFile.GetMemberVariables(), true );
}

// ^^x
// void CVariableRulesModule::ProcessSourceFile
// 3BGO NTP-1 25-10-2020
void CVariableRulesModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    CalculateStatistics( oSourceFile.GetGlobalFunctions() );
    CalculateStatistics( oSourceFile.GetMemberFunctions() );
}

// ^^x
// void CVariableRulesModule::OnPostExecute
// 3BGO NTP-1 25-10-2020
void CVariableRulesModule::OnPostExecute( CStatisticsCollection& oFinalStatisticsCollection )
{
    const std::size_t uiVariableCount = m_oVariableSet.size();
    const std::size_t uiMemberVariableCount = m_oMemberVariableSet.size();

    m_oStatisticsCollection.SetStatisticsValue( EStatisticsTypes::eVariableIncorrectNameCount, ( uiVariableCount + uiMemberVariableCount ) );

    oFinalStatisticsCollection.MergeStatistics( m_oStatisticsCollection );
}

// ^^x
// void CVariableRulesModule::OnCollectedStatistics
// 3BGO NTP-1 11-01-2021
void CVariableRulesModule::OnCollectedStatistics( CStatisticsCollection& )
{
    if ( IsLoggingEnabled() )
    {
        if ( !m_oVariableSet.empty() || !m_oMemberVariableSet.empty() )
        {
            m_oLogger.Open( "IncorrectVariableNames.txt" );

            std::for_each( m_oVariableSet.cbegin(), m_oVariableSet.cend(), [this]( const SFindDataResult<CVariable>& oVariable )
            {
                m_oLogger.Log( oVariable );
            } );

            std::for_each( m_oMemberVariableSet.cbegin(), m_oMemberVariableSet.cend(), [this]( const SFindDataResult<CVariable>& oVariable )
            {
                m_oLogger.Log( oVariable, true );
            } );
        }
    }
}

// ^^x
// void CVariableRulesModule::CalculateStatistics
// 3BGO NTP-1 25-10-2020
void CVariableRulesModule::CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector )
{
    for ( const SFindDataResult<CFunction>& oFunction : oFunctionVector )
    {
        std::optional<std::vector<SFindDataResult<CVariable>>> oVariableVector = oFunction.oData.GetLocalVariables();

        if ( oVariableVector.has_value() )
        {
            ValidateVariables( *oVariableVector, false );
        }
    }
}

// ^^x
// void CVariableRulesModule::ValidateVariables
// 3BGO NTP-1 25-10-2020
void CVariableRulesModule::ValidateVariables( const std::vector<SFindDataResult<CVariable>>& oVariableVector, const bool bIsMember )
{
    for ( const SFindDataResult<CVariable>& oVariable : oVariableVector )
    {
        SVariableNameRule oVariableNameRule{};
        HasVariablePrimitiveType( oVariable.oData, oVariableNameRule );

        if ( !IsVariableNameCorrect( oVariable.oData, bIsMember, oVariableNameRule ) )
        {
            if ( bIsMember )
            {
                m_oMemberVariableSet.insert( oVariable );
            }
            else
            {
                m_oVariableSet.insert( oVariable );
            }
        }
    }
}

// ^^x
// std::string CVariableRulesModule::CorrectPrefixName
// 3BGO NTP-1 28-10-2020
std::string CVariableRulesModule::CorrectPrefixName( const CVariable& oVariable, const bool bIsMember, const SVariableNameRule& oVariableNameRule ) const
{
    std::string oCorrectPrefixNameString{};

    if ( bIsMember )
    {
        oCorrectPrefixNameString.append( "m_" );
    }

    if ( oVariable.IsArrayType() )
    {
        oCorrectPrefixNameString.append( "a" );
    }

    if ( oVariable.GetReferenceType().has_value() )
    {
        if ( oVariable.GetReferenceType() == CVariable::EReferenceType::Pointer )
        {
            oCorrectPrefixNameString.append( "p" );
        }
    }

    if ( oVariable.GetType().find( "unsigned" ) != std::string::npos )
    {
        oCorrectPrefixNameString.append( "u" );
    }

    oCorrectPrefixNameString.append( oVariableNameRule.oPrefixString );

    return oCorrectPrefixNameString;
}

// ^^x
// std::string CVariableRulesModule::SimplifyVariableType
// 3BGO NTP-1 28-10-2020
std::string CVariableRulesModule::SimplifyVariableType( const CVariable& oVariable ) const
{
    std::string oVariableTypeString = CStringHelper::Trim( oVariable.GetType() );

    oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "static" );
    oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "constexpr" );
    oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "const" );
    oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "unsigned" );
    oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "*" );
    oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "&" );
    oVariableTypeString = CStringHelper::Trim( oVariableTypeString );

    return oVariableTypeString;
}

// ^^x
// bool CVariableRulesModule::IsVariableNameCorrect
// 3BGO NTP-1 28-10-2020
bool CVariableRulesModule::IsVariableNameCorrect( const CVariable& oVariable, const bool bIsMember, const SVariableNameRule& oVariableNameRule ) const
{
    bool bIsNameFirstCharacterCorrect{ false };

    const bool bIsPrefixNameCorrect = IsVariablePrefixNameCorrect( oVariable, bIsMember, oVariableNameRule );
    if ( bIsPrefixNameCorrect )
    {
        if ( oVariableNameRule.oPrefixString.empty() )
        {
            bIsNameFirstCharacterCorrect = true;
        }
        else
        {
            bIsNameFirstCharacterCorrect = IsVariableNameFirstCharacterCorrect( oVariable, bIsMember, oVariableNameRule );
        }
    }

    return bIsPrefixNameCorrect && bIsNameFirstCharacterCorrect;
}

// ^^x
// bool CVariableRulesModule::IsVariableNameFirstCharacterCorrect
// 3BGO NTP-1 28-10-2020
bool CVariableRulesModule::IsVariableNameFirstCharacterCorrect( const CVariable& oVariable, const bool bIsMember, const SVariableNameRule& oVariableNameRule ) const
{
    bool bIsNameStartsWithCapitalCharacter{ false };

    const std::string oCorrectTypePrefixName = CorrectPrefixName( oVariable, bIsMember, oVariableNameRule );
    const std::string& oVariableNameString = oVariable.GetName();

    if ( oCorrectTypePrefixName.size() < oVariableNameString.size() )
    {
        const unsigned char cFirstNameCharacter = oVariableNameString[oCorrectTypePrefixName.size()];
        bIsNameStartsWithCapitalCharacter = !std::islower( cFirstNameCharacter, {} );
    }

    return bIsNameStartsWithCapitalCharacter;
}

// ^^x
// bool CVariableRulesModule::IsVariablePrefixNameCorrect
// 3BGO NTP-1 28-10-2020
bool CVariableRulesModule::IsVariablePrefixNameCorrect( const CVariable& oVariable, const bool bIsMember, const SVariableNameRule& oVariableNameRule ) const
{
    const std::string oCorrectTypePrefixName = CorrectPrefixName( oVariable, bIsMember, oVariableNameRule );
    const std::string& oVariableNameString = oVariable.GetName();

    return ( oVariableNameString.find( oCorrectTypePrefixName ) == 0u );
}

// ^^x
// bool CVariableRulesModule::HasVariablePrimitiveType
// 3BGO NTP-1 28-10-2020
bool CVariableRulesModule::HasVariablePrimitiveType( const CVariable& oVariable, SVariableNameRule& oVariableNameRule ) const
{
    VariableNameRuleArray::const_iterator oRuleIt = std::find_if( m_aoVariableNameRules.cbegin(), m_aoVariableNameRules.cend(), [oTypeString = SimplifyVariableType( oVariable )]( const SVariableNameRule& oVariableNameRule )
    {
        return oVariableNameRule.oVariableTypeString == oTypeString;
    } );

    const bool bIsFundamentalType = ( oRuleIt != m_aoVariableNameRules.cend() );
    if ( bIsFundamentalType )
    {
        oVariableNameRule = *oRuleIt;
    }

    return bIsFundamentalType;
}
