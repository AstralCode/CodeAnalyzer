#include "GlobalCountModule.h"

#include <iostream>
#include "StringHelper.h"

#include "SourceFile.h"

// ^^x
// CCodeLineCountModule::CCodeLineCountModule
// 3BGO JIRA-238 15-10-2020
CGlobalCountModule::CGlobalCountModule()
{
    CreateStatistics( "Global Variables" );
    CreateStatistics( "Global Functions" );
}

// ^^x
// void CCodeLineCountModule::ProcessHeaderFile
// 3BGO JIRA-238 15-10-2020
void CGlobalCountModule::ProcessHeaderFile( const CHeaderFile& )
{
}

// ^^x
// void CCodeLineCountModule::ProcessSourceFile
// 3BGO JIRA-238 15-10-2020
void CGlobalCountModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    GetStatistics( EStatisticsId::eGlobalVariables ).uiValue += oSourceFile.GetGlobalVariables().size();
    GetStatistics( EStatisticsId::eGlobalFunctions ).uiValue += oSourceFile.GetGlobalFunctions().size();
}
