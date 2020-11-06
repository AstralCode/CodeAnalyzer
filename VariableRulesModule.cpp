#include "VariableRulesModule.h"

#include "SourceFile.h"
#include "StatisticsCollection.h"
#include "StringHelper.h"

const std::array<CVariableRulesModule::SVariablePrimitiveTypeNameRule, 13u> CVariableRulesModule::m_aoVariablePrimitiveTypeNameRules =
{
    CVariableRulesModule::SVariablePrimitiveTypeNameRule{ "char", "c" },
    CVariableRulesModule::SVariablePrimitiveTypeNameRule{ "bool", "b" },
    CVariableRulesModule::SVariablePrimitiveTypeNameRule{ "BOOL", "b" },
    CVariableRulesModule::SVariablePrimitiveTypeNameRule{ "int", "i" },
    CVariableRulesModule::SVariablePrimitiveTypeNameRule{ "WORD", "w" },
    CVariableRulesModule::SVariablePrimitiveTypeNameRule{ "DWORD", "dw" },
    CVariableRulesModule::SVariablePrimitiveTypeNameRule{ "short", "s" },
    CVariableRulesModule::SVariablePrimitiveTypeNameRule{ "long", "l" },
    CVariableRulesModule::SVariablePrimitiveTypeNameRule{ "long long", "ll" },
    CVariableRulesModule::SVariablePrimitiveTypeNameRule{ "float", "f" },
    CVariableRulesModule::SVariablePrimitiveTypeNameRule{ "double", "d" },
    CVariableRulesModule::SVariablePrimitiveTypeNameRule{ "long double", "ld" }
};

// ^^x
// void CVariableRulesModule::OnPreExecute
// 3BGO JIRA-238 25-10-2020
void CVariableRulesModule::OnPreExecute( CStatisticsCollection& oStatisticsCollection )
{
    oStatisticsCollection[EStatisticsTypes::eVariableIncorrectNameCount].oHeaderString = "Incorrect Variable Names";
}

// ^^x
// void CVariableRulesModule::ProcessHeaderFile
// 3BGO JIRA-238 25-10-2020
void CVariableRulesModule::ProcessHeaderFile( const CHeaderFile&, CStatisticsCollection& )
{

}

// ^^x
// void CVariableRulesModule::ProcessSourceFile
// 3BGO JIRA-238 25-10-2020
void CVariableRulesModule::ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection )
{
    CalculateStatistics( oSourceFile.GetGlobalFunctions(), oStatisticsCollection );
    CalculateStatistics( oSourceFile.GetMemberFunctions(), oStatisticsCollection );
}

// ^^x
// void CVariableRulesModule::OnPostExecute
// 3BGO JIRA-238 25-10-2020
void CVariableRulesModule::OnPostExecute( CStatisticsCollection& )
{

}

// ^^x
// void CVariableRulesModule::CalculateStatistics
// 3BGO JIRA-238 25-10-2020
void CVariableRulesModule::CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector, CStatisticsCollection& oStatisticsCollection )
{
    for ( const SFindDataResult<CFunction>& oFunction : oFunctionVector )
    {
        std::optional<std::vector<SFindDataResult<CVariable>>> oVariableVector = oFunction.oData.GetLocalVariables();

        if ( oVariableVector.has_value() )
        {
            ValidateVariables( *oVariableVector, oStatisticsCollection );
        }
    }
}

// ^^x
// void CVariableRulesModule::ValidateVariables
// 3BGO JIRA-238 25-10-2020
void CVariableRulesModule::ValidateVariables( const std::vector<SFindDataResult<CVariable>>& oVariableVector, CStatisticsCollection& oStatisticsCollection ) const
{
    SVariablePrimitiveTypeNameRule oVariableNameRule{};

    for ( const SFindDataResult<CVariable>& oVariable : oVariableVector )
    {
        if ( HasVariablePrimitiveType( oVariable.oData, oVariableNameRule ) )
        {
            if ( !IsVariableNameCorrect( oVariable.oData, oVariableNameRule ) )
            {
                ++oStatisticsCollection[EStatisticsTypes::eVariableIncorrectNameCount].uiValue;
            }
        }
    }
}

// ^^x
// std::string CVariableRulesModule::CorrectPrefixName
// 3BGO JIRA-238 28-10-2020
std::string CVariableRulesModule::CorrectPrefixName( const CVariable& oVariable, const SVariablePrimitiveTypeNameRule& oVariableNameRule ) const
{
    std::string oCorrectPrefixNameString{};

    if ( oVariable.GetReferenceType().has_value() )
    {
        if ( oVariable.GetReferenceType() == CVariable::EReferenceType::Pointer )
        {
            oCorrectPrefixNameString.append( "p" );
        }
    }

    if ( oVariable.IsArrayType() )
    {
        oCorrectPrefixNameString.append( "a" );
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
// 3BGO JIRA-238 28-10-2020
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
// 3BGO JIRA-238 28-10-2020
bool CVariableRulesModule::IsVariableNameCorrect( const CVariable& oVariable, const SVariablePrimitiveTypeNameRule& oVariableNameRule ) const
{
    bool bIsNameFirstCharacterCorrect{ false };

    const bool bIsPrefixNameCorrect = IsVariablePrefixNameCorrect( oVariable, oVariableNameRule );
    if ( bIsPrefixNameCorrect )
    {
        bIsNameFirstCharacterCorrect = IsVariableNameFirstCharacterCorrect( oVariable, oVariableNameRule );
    }

    return bIsPrefixNameCorrect && bIsNameFirstCharacterCorrect;
}

// ^^x
// bool CVariableRulesModule::IsVariableNameFirstCharacterCorrect
// 3BGO JIRA-238 28-10-2020
bool CVariableRulesModule::IsVariableNameFirstCharacterCorrect( const CVariable& oVariable, const SVariablePrimitiveTypeNameRule& oVariableNameRule ) const
{
    bool bIsNameStartsWithCapitalCharacter{ false };

    const std::string oCorrectTypePrefixName = CorrectPrefixName( oVariable, oVariableNameRule );
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
// 3BGO JIRA-238 28-10-2020
bool CVariableRulesModule::IsVariablePrefixNameCorrect( const CVariable& oVariable, const SVariablePrimitiveTypeNameRule& oVariableNameRule ) const
{
    const std::string oCorrectTypePrefixName = CorrectPrefixName( oVariable, oVariableNameRule );
    const std::string& oVariableNameString = oVariable.GetName();

    return ( oVariableNameString.find( oCorrectTypePrefixName ) == 0u );
}

// ^^x
// bool CVariableRulesModule::HasVariablePrimitiveType
// 3BGO JIRA-238 28-10-2020
bool CVariableRulesModule::HasVariablePrimitiveType( const CVariable& oVariable, SVariablePrimitiveTypeNameRule& oVariableNameRule ) const
{
    std::array<SVariablePrimitiveTypeNameRule, 13u>::const_iterator oRuleIt = std::find_if( m_aoVariablePrimitiveTypeNameRules.cbegin(), m_aoVariablePrimitiveTypeNameRules.cend(), [oTypeString = SimplifyVariableType( oVariable )]( const SVariablePrimitiveTypeNameRule& oVariableNameRule )
    {
        return oVariableNameRule.oVariableTypeString == oTypeString;
    } );

    const bool bIsFundamentalType = oRuleIt != m_aoVariablePrimitiveTypeNameRules.cend();
    if ( bIsFundamentalType )
    {
        oVariableNameRule = *oRuleIt;
    }

    return bIsFundamentalType;
}
