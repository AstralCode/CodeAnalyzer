#include "CodeFileLineCountModule.h"

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
void CCodeFileLineCountModule::ProcessHeaderFile( const CHeaderCodeFile& )
{

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
// std::string CCodeFileLineCountModule::GetStatisticsHeader
// 3BGO JIRA-238 24-09-2020
std::string CCodeFileLineCountModule::GetStatisticsHeader() const
{
    return { "Code Line Count" };
}

// ^^x
// unsigned int CCodeFileLineCountModule::GetStatisticsResult
// 3BGO JIRA-238 24-09-2020
unsigned int CCodeFileLineCountModule::GetStatisticsResult() const
{
    return m_uiStatisticsResult;
}
