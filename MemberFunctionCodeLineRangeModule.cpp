#include "MemberFunctionCodeLineRangeModule.h"

// ^^x
// CMemberFunctionCodeLineRangeModule::CMemberFunctionCodeLineRangeModule
// 3BGO JIRA-239 30-09-2020
CMemberFunctionCodeLineRangeModule::CMemberFunctionCodeLineRangeModule( CCodeParser& oCodeParser ) :
    CStatisticsAnalyzerModule{ oCodeParser }
{
    CreateStatistics( "Function Code Line Range[0-20]" );
    CreateStatistics( "Function Code Line Range[21-50]" );
    CreateStatistics( "Function Code Line Range[51-100]" );
    CreateStatistics( "Function Code Line Range[101-300]" );
    CreateStatistics( "Function Code Line Range[301-more]" );
}

// ^^x
// void CMemberFunctionCodeLineRangeModule::PreProcessCodeFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionCodeLineRangeModule::PreProcessCodeFile( const CCodeFile& )
{

}

// ^^x
// void CMemberFunctionCodeLineRangeModule::ProcessCodeFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionCodeLineRangeModule::ProcessCodeFile( const CCodeFile& )
{

}

// ^^x
// void CMemberFunctionCodeLineRangeModule::PostProcessCodeFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionCodeLineRangeModule::PostProcessCodeFile( const CCodeFile& )
{

}

// ^^x
// std::string CMemberFunctionCodeLineRangeModule::GetModuleName
// 3BGO JIRA-238 01-10-2020
std::string CMemberFunctionCodeLineRangeModule::GetModuleName() const
{
    return "Function Code Line Range Counter";
}
