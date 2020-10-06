#include "CodeFileLineCountModule.h"

#include "HeaderFile.h"
#include "SourceFile.h"

// ^^x
// CCodeFileLineCountModule::CCodeFileLineCountModule
// 3BGO JIRA-238 24-09-2020
CCodeFileLineCountModule::CCodeFileLineCountModule()
{
    CreateStatistics( "Code Line Count" );
}

// ^^x
// void CCodeFileLineCountModule::ProcessHeaderFile
// 3BGO JIRA-238 24-09-2020
void CCodeFileLineCountModule::ProcessHeaderFile( const CHeaderFile& oHeaderFile )
{
    GetStatistics( 0u ).uiValue += oHeaderFile.GetCodeLineCount();
}

// ^^x
// void CCodeFileLineCountModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CCodeFileLineCountModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    GetStatistics( 0u ).uiValue += oSourceFile.GetCodeLineCount();
}
