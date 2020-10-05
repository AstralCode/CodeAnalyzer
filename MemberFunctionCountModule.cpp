#include "MemberFunctionCountModule.h"

// ^^x
// CMemberFunctionCountModule::CMemberFunctionCountModule
// 3BGO JIRA-239 01-10-2020
CMemberFunctionCountModule::CMemberFunctionCountModule( CCodeParser& oCodeParser ) :
    CStatisticsAnalyzerModule{ oCodeParser }
{
    CreateStatistics( "Function Count" );
}

// ^^x
// void CMemberFunctionCountModule::PreProcessCodeFile
// 3BGO JIRA-239 01-10-2020
void CMemberFunctionCountModule::PreProcessCodeFile( const CCodeFile& )
{

}

// ^^x
// void CMemberFunctionCountModule::ProcessCodeFile
// 3BGO JIRA-239 01-10-2020
void CMemberFunctionCountModule::ProcessCodeFile( const CCodeFile& oCodeFile )
{
    if ( oCodeFile.GetType() == CCodeFile::EType::eSource )
    {
        GetStatistics( 0u ).uiValue += oCodeFile.GetMemberFunctionDataset().size();
    }
}

// ^^x
// void CMemberFunctionCountModule::PostProcessCodeFile
// 3BGO JIRA-239 01-10-2020
void CMemberFunctionCountModule::PostProcessCodeFile( const CCodeFile& )
{

}

// ^^x
// std::string CMemberFunctionCountModule::GetModuleName
// 3BGO JIRA-238 01-10-2020
std::string CMemberFunctionCountModule::GetModuleName() const
{
    return "Function Counter";
}

