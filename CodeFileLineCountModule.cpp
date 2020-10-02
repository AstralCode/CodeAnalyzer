#include "CodeFileLineCountModule.h"

// ^^x
// CCodeFileLineCountModule::CCodeFileLineCountModule
// 3BGO JIRA-238 24-09-2020
CCodeFileLineCountModule::CCodeFileLineCountModule( CCodeParser& oCodeParser ) :
    CStatisticsAnalyzerModule{ oCodeParser }
{
    CreateStatistics( "Code Line Count" );
}

// ^^x
// void CCodeFileLineCountModule::PreProcessCodeFile
// 3BGO JIRA-238 24-09-2020
void CCodeFileLineCountModule::PreProcessCodeFile( const CCodeFile& )
{

}

// ^^x
// void CCodeFileLineCountModule::ProcessCodeFile
// 3BGO JIRA-238 24-09-2020
void CCodeFileLineCountModule::ProcessCodeFile( const CCodeFile& oCodeFile )
{
    if ( oCodeFile.GetType() == CCodeFile::EType::eHeader || oCodeFile.GetType() == CCodeFile::EType::eSource )
    {
        GetStatistics( 0u ).uiValue += oCodeFile.GetCodeLines().size();
    }
}

// ^^x
// void CCodeFileLineCountModule::PostProcessCodeFile
// 3BGO JIRA-238 24-09-2020
void CCodeFileLineCountModule::PostProcessCodeFile( const CCodeFile& )
{

}

// ^^x
// std::string CCodeFileLineCountModule::GetModuleName
// 3BGO JIRA-238 01-10-2020
std::string CCodeFileLineCountModule::GetModuleName() const
{
    return "Code Line Counter";
}