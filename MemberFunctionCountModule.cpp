#include "MemberFunctionCountModule.h"

#include "SourceCodeFile.h"

constexpr const char* MODULE_HEADER_STR = "Functions";

// ^^x
// CMemberFunctionCountModule::CMemberFunctionCountModule
// 3BGO JIRA-238 24-09-2020
CMemberFunctionCountModule::CMemberFunctionCountModule() :
    m_uiStatisticsResult{ 0u }
{

}

// ^^x
// void CMemberFunctionCountModule::OnStartProcess
// 3BGO JIRA-238 24-09-2020
void CMemberFunctionCountModule::OnStartProcess( const CCodeFile& )
{

}

// ^^x
// void CMemberFunctionCountModule::ProcessHeaderFile
// 3BGO JIRA-238 24-09-2020
void CMemberFunctionCountModule::ProcessHeaderFile( const CHeaderCodeFile& )
{

}

// ^^x
// void CMemberFunctionCountModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CMemberFunctionCountModule::ProcessSourceFile( const CSourceCodeFile& oSourceCodeFile )
{
    m_uiStatisticsResult += oSourceCodeFile.FindMemberFunctionHeaders().size();
}

// ^^x
// void CMemberFunctionCountModule::OnEndProcess
// 3BGO JIRA-238 24-09-2020
void CMemberFunctionCountModule::OnEndProcess( const CCodeFile& )
{

}

// ^^x
// std::string CMemberFunctionCountModule::GetStatisticsHeader
// 3BGO JIRA-238 24-09-2020
std::string CMemberFunctionCountModule::GetStatisticsHeader() const
{
    return MODULE_HEADER_STR;
}

// ^^x
// unsigned int CMemberFunctionCountModule::GetStatisticsResult
// 3BGO JIRA-238 24-09-2020
unsigned int CMemberFunctionCountModule::GetStatisticsResult() const
{
    return m_uiStatisticsResult;
}
