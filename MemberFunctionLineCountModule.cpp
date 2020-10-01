#include "MemberFunctionLineCountModule.h"

#include "SourceCodeFile.h"

constexpr const char* MODULE_HEADER_STR = "Function Lines";

// ^^x
// CMemberFunctionLineCountModule::CMemberFunctionLineCountModule
// 3BGO JIRA-239 30-09-2020
CMemberFunctionLineCountModule::CMemberFunctionLineCountModule() :
    m_uiStatisticsResult{ 0u }
{

}

// ^^x
// void CMemberFunctionLineCountModule::OnStartProcess
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionLineCountModule::OnStartProcess( const CCodeFile& )
{

}

// ^^x
// void CMemberFunctionLineCountModule::ProcessHeaderFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionLineCountModule::ProcessHeaderFile( const CHeaderCodeFile& )
{

}

// ^^x
// void CMemberFunctionLineCountModule::ProcessSourceFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionLineCountModule::ProcessSourceFile( const CSourceCodeFile& )
{

}

// ^^x
// void CMemberFunctionLineCountModule::OnEndProcess
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionLineCountModule::OnEndProcess( const CCodeFile& )
{

}

// ^^x
// std::string CMemberFunctionLineCountModule::GetStatisticsHeader
// 3BGO JIRA-239 30-09-2020
std::string CMemberFunctionLineCountModule::GetStatisticsHeader() const
{
    return MODULE_HEADER_STR;
}

// ^^x
// unsigned int CMemberFunctionLineCountModule::GetStatisticsResult
// 3BGO JIRA-239 30-09-2020
unsigned int CMemberFunctionLineCountModule::GetStatisticsResult() const
{
    return m_uiStatisticsResult;
}
