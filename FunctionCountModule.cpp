#include "FunctionCountModule.h"

#include "SourceFile.h"

// ^^x
// CFunctionCountModule::CFunctionCountModule
// 3BGO JIRA-238 01-10-2020
CFunctionCountModule::CFunctionCountModule()
{
    CreateStatistics( "Functions" );
    CreateStatistics( "Member Functions" );
    CreateStatistics( "%" );
    CreateStatistics( "Global Functions" );
    CreateStatistics( "%" );
}

// ^^x
// void CFunctionCountModule::ProcessHeaderFile
// 3BGO JIRA-238 01-10-2020
void CFunctionCountModule::ProcessHeaderFile( const CHeaderFile& )
{

}

// ^^x
// void CFunctionCountModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CFunctionCountModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    const std::size_t uiMemberFunctionCount = oSourceFile.GetMemberFunctions().size();
    const std::size_t uiGlobalFunctionCount = oSourceFile.GetGlobalFunctions().size();

    GetStatistics( EStatisticsId::eFunctions ).uiValue += uiMemberFunctionCount;
    GetStatistics( EStatisticsId::eFunctions ).uiValue += uiGlobalFunctionCount;

    GetStatistics( EStatisticsId::eMemberFunctions ).uiValue += uiMemberFunctionCount;
    GetStatistics( EStatisticsId::eGlobalFunctions ).uiValue += uiGlobalFunctionCount;
}

// ^^x
// void CFunctionCountModule::OnComplete
// 3BGO JIRA-238 23-10-2020
void CFunctionCountModule::OnComplete()
{
    const std::size_t uiTotalSumStatisticsValue = GetStatistics( EStatisticsId::eFunctions ).uiValue;

    ToPercent( EStatisticsId::eMemberFunctionsPercent, EStatisticsId::eMemberFunctions, uiTotalSumStatisticsValue );
    ToPercent( EStatisticsId::eGlobalFunctionsPercent, EStatisticsId::eGlobalFunctions, uiTotalSumStatisticsValue );
}
