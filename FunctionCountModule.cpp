#include "FunctionCountModule.h"

#include "SourceFile.h"

// ^^x
// CFunctionCountModule::CFunctionCountModule
// 3BGO JIRA-239 01-10-2020
CFunctionCountModule::CFunctionCountModule()
{
    CreateStatistics( "Functions" );
}

// ^^x
// void CFunctionCountModule::ProcessHeaderFile
// 3BGO JIRA-239 01-10-2020
void CFunctionCountModule::ProcessHeaderFile( const CHeaderFile& )
{

}

// ^^x
// void CFunctionCountModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CFunctionCountModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    GetStatistics( EStatisticsId::eTotalFunctionCount ).uiValue += oSourceFile.GetGlobalFunctions().size();
    GetStatistics( EStatisticsId::eTotalFunctionCount ).uiValue += oSourceFile.GetMemberFunctions().size();
}
