#include "MemberFunctionLineCountRangeModule.h"

// ^^x
// CMemberFunctionLineCountRangeModule::CMemberFunctionLineCountRangeModule
// 3BGO JIRA-239 30-09-2020
CMemberFunctionLineCountRangeModule::CMemberFunctionLineCountRangeModule( CCodeParser& oCodeParser ) :
    CStatisticsAnalyzerModule{ oCodeParser }
{
    CreateStatistics( "Function Code Line Count[0-20]" );
    CreateStatistics( "Function Code Line Count[21-50]" );
    CreateStatistics( "Function Code Line Count[51-100]" );
    CreateStatistics( "Function Code Line Count[101-300]" );
    CreateStatistics( "Function Code Line Count[301-more]" );
}

// ^^x
// void CMemberFunctionLineCountRangeModule::PreProcessCodeFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionLineCountRangeModule::PreProcessCodeFile( const CCodeFile& )
{

}

// ^^x
// void CMemberFunctionLineCountRangeModule::ProcessCodeFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionLineCountRangeModule::ProcessCodeFile( const CCodeFile& )
{

}

// ^^x
// void CMemberFunctionLineCountRangeModule::PostProcessCodeFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionLineCountRangeModule::PostProcessCodeFile( const CCodeFile& )
{

}

// ^^x
// std::string CMemberFunctionLineCountRangeModule::GetModuleName
// 3BGO JIRA-238 01-10-2020
std::string CMemberFunctionLineCountRangeModule::GetModuleName() const
{
    return "Function Code Line Range Counter";
}
