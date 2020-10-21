#include "CodeLineCountModule.h"

#include "HeaderFile.h"
#include "SourceFile.h"

// ^^x
// CCodeLineCountModule::CCodeLineCountModule
// 3BGO JIRA-238 24-09-2020
CCodeLineCountModule::CCodeLineCountModule()
{
    CreateStatistics( "Code Lines" );
}

// ^^x
// void CCodeLineCountModule::ProcessHeaderFile
// 3BGO JIRA-238 24-09-2020
void CCodeLineCountModule::ProcessHeaderFile( const CHeaderFile& oHeaderFile )
{
    GetStatistics( EStatisticsId::eTotalCodeLineCount ).uiValue += oHeaderFile.GetCodeLineCount();
}

// ^^x
// void CCodeLineCountModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CCodeLineCountModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    GetStatistics( EStatisticsId::eTotalCodeLineCount ).uiValue += oSourceFile.GetCodeLineCount();
}
