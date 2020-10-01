#include "CodeFileLineCountModule.h"

#include "HeaderCodeFile.h"
#include "SourceCodeFile.h"

// ^^x
// CCodeFileLineCountModule::CCodeFileLineCountModule
// 3BGO JIRA-238 24-09-2020
CCodeFileLineCountModule::CCodeFileLineCountModule() :
    m_uiStatisticsResult{ 0u }
{

}

// ^^x
// void CCodeFileLineCountModule::OnStartProcess
// 3BGO JIRA-238 24-09-2020
void CCodeFileLineCountModule::OnStartProcess( const CCodeFile& )
{

}

// ^^x
// void CCodeFileLineCountModule::ProcessHeaderFile
// 3BGO JIRA-238 24-09-2020
void CCodeFileLineCountModule::ProcessHeaderFile( const CHeaderCodeFile& oHeaderCodeFile )
{
    m_uiStatisticsResult += oHeaderCodeFile.GetCodeLines().size();
}

// ^^x
// void CCodeFileLineCountModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CCodeFileLineCountModule::ProcessSourceFile( const CSourceCodeFile& oSourceCodeFile )
{
    m_uiStatisticsResult += oSourceCodeFile.GetCodeLines().size();
}

// ^^x
// void CCodeFileLineCountModule::OnEndProcess
// 3BGO JIRA-238 24-09-2020
void CCodeFileLineCountModule::OnEndProcess( const CCodeFile& )
{

}

// ^^x
// std::string CCodeFileLineCountModule::GetModuleName
// 3BGO JIRA-238 01-10-2020
std::string CCodeFileLineCountModule::GetModuleName() const
{
    return "Code Line Counter";
}

// ^^x
// std::vector<SStatisticsResult> CCodeFileLineCountModule::GetStatistics
// 3BGO JIRA-238 24-09-2020
std::vector<SStatisticsResult> CCodeFileLineCountModule::GetStatistics() const
{
    return { { "Code Line Count", m_uiStatisticsResult } };
}
