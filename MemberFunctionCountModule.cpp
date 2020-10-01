#include "MemberFunctionCountModule.h"

#include "SourceCodeFile.h"

// ^^x
// CMemberFunctionCountModule::CMemberFunctionCountModule
// 3BGO JIRA-239 01-10-2020
CMemberFunctionCountModule::CMemberFunctionCountModule() :
    m_uiStatisticsResult{ 0u }
{

}

// ^^x
// void CMemberFunctionCountModule::OnStartProcessFile
// 3BGO JIRA-239 01-10-2020
void CMemberFunctionCountModule::OnStartProcessFile( const CCodeFile& )
{

}

// ^^x
// void CMemberFunctionCountModule::ProcessHeaderFile
// 3BGO JIRA-239 01-10-2020
void CMemberFunctionCountModule::ProcessHeaderFile( const CHeaderCodeFile& )
{

}

// ^^x
// void CMemberFunctionCountModule::ProcessSourceFile
// 3BGO JIRA-239 01-10-2020
void CMemberFunctionCountModule::ProcessSourceFile( const CSourceCodeFile& oSourceCodeFile )
{
    m_uiStatisticsResult += oSourceCodeFile.FindMemberFunctionHeader().size();
}

// ^^x
// void CMemberFunctionCountModule::OnEndProcessFile
// 3BGO JIRA-239 01-10-2020
void CMemberFunctionCountModule::OnEndProcessFile( const CCodeFile& )
{

}

// ^^x
// std::string CMemberFunctionCountModule::GetModuleName
// 3BGO JIRA-238 01-10-2020
std::string CMemberFunctionCountModule::GetModuleName() const
{
    return "Function Counter";
}

// ^^x
// std::vector<SStatisticsResult> CMemberFunctionCountModule::GetStatistics
// 3BGO JIRA-238 24-09-2020
std::vector<SStatisticsResult> CMemberFunctionCountModule::GetStatistics() const
{
    return { { "Function Count", m_uiStatisticsResult } };
}
