#include "VariableRulesModule.h"

#include "SourceFile.h"
#include "StatisticsCollection.h"
#include "StringHelper.h"

const std::array<CVariableRulesModule::SVariableNameRule, 8u> CVariableRulesModule::m_aoVariableNameRules =
{
    CVariableRulesModule::SVariableNameRule{ "char", "c", std::nullopt },
    CVariableRulesModule::SVariableNameRule{ "unsigned char", "uc", std::nullopt },
    CVariableRulesModule::SVariableNameRule{ "bool", "b", std::nullopt },
    CVariableRulesModule::SVariableNameRule{ "int", "i", std::nullopt },
    CVariableRulesModule::SVariableNameRule{ "unsigned int", "ui", std::nullopt },
    CVariableRulesModule::SVariableNameRule{ "float", "f", std::nullopt },
    CVariableRulesModule::SVariableNameRule{ "double", "d", std::nullopt },
    CVariableRulesModule::SVariableNameRule{ "CString", "o", "String" }
};

// ^^x
// void CVariableRulesModule::OnPreExecute
// 3BGO JIRA-238 25-10-2020
void CVariableRulesModule::OnPreExecute( CStatisticsCollection& oStatisticsCollection )
{
    oStatisticsCollection[EStatisticsTypes::eVariableIncorrectNameCount].oHeaderString = "Variable Incorrect Names";
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
    for ( const SFindDataResult<CVariable>& oVariable : oVariableVector )
    {
        std::string oVariableTypeString = CStringHelper::Trim( oVariable.oData.GetType() );
        oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "static" );
        oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "constexpr" );
        oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "const" );
        oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "&" );
        
        const std::string oVariableNameString = CStringHelper::Trim( oVariable.oData.GetName() );

        for ( const SVariableNameRule& oVariableNameRule : m_aoVariableNameRules )
        {
            if ( oVariableTypeString == oVariableNameRule.oVariableTypeString )
            {
                std::string oVariablePrefixString{};
                if ( oVariableTypeString.find( '*' ) != std::string::npos )
                {
                    oVariablePrefixString.append( "p" );
                }

                oVariablePrefixString.append( oVariableNameRule.oPrefixString );

                const std::string::size_type uiVariablePrefixNamePos = oVariableNameString.find( oVariableNameRule.oPrefixString );
                
                if ( uiVariablePrefixNamePos != 0u )
                {
                    ++oStatisticsCollection[EStatisticsTypes::eVariableIncorrectNameCount].uiValue;
                }

                break;
            }
        }
    }
}
