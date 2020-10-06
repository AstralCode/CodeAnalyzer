#include "MemberFunctionCountModule.h"

#include "SourceFile.h"

// ^^x
// CMemberFunctionCountModule::CMemberFunctionCountModule
// 3BGO JIRA-239 01-10-2020
CMemberFunctionCountModule::CMemberFunctionCountModule()
{
    CreateStatistics( "Function Count" );
}

// ^^x
// void CMemberFunctionCountModule::ProcessHeaderFile
// 3BGO JIRA-239 01-10-2020
void CMemberFunctionCountModule::ProcessHeaderFile( const CHeaderFile& )
{

}

// ^^x
// void CMemberFunctionCountModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CMemberFunctionCountModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    GetStatistics( 0u ).uiValue += oSourceFile.GetMemberFunctions().size();
}
