#include "CodeLineCountModule.h"

#include <iostream>

#include "ProgramStatusCodes.h"

constexpr const char* MODULE_HEADER_STR = "CodeLineCount";

// ^^x
// CCodeLineCountModule::CCodeLineCountModule
// 3BGO JIRA-238 24-09-2020
CCodeLineCountModule::CCodeLineCountModule() :
    m_uiStatisticsResult{ 0u }
{

}

// ^^x
// void CCodeLineCountModule::OnStartProcess
// 3BGO JIRA-238 24-09-2020
void CCodeLineCountModule::OnStartProcess( const CCodeFile& oCodeFile )
{
    std::cout << "CCodeLineCountModule::OnStartProcess: " << oCodeFile.GetPath().string() << std::endl;
}

// ^^x
// void CCodeLineCountModule::ProcessHeaderFile
// 3BGO JIRA-238 24-09-2020
void CCodeLineCountModule::ProcessHeaderFile( const CHeaderCodeFile& oHeaderCodeFile )
{

}

// ^^x
// void CCodeLineCountModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CCodeLineCountModule::ProcessSourceFile( const CSourceCodeFile& oSourceCodeFile )
{

}

// ^^x
// void CCodeLineCountModule::OnEndProcess
// 3BGO JIRA-238 24-09-2020
void CCodeLineCountModule::OnEndProcess( const CCodeFile& oCodeFile )
{
    std::cout << "CCodeLineCountModule::OnEndProcess: " << oCodeFile.GetPath().string() << std::endl;
}

// ^^x
// std::string CCodeLineCountModule::GetStatisticsHeader
// 3BGO JIRA-238 24-09-2020
std::string CCodeLineCountModule::GetStatisticsHeader() const
{
    return MODULE_HEADER_STR;
}

// ^^x
// unsigned int CCodeLineCountModule::GetStatisticsResult
// 3BGO JIRA-238 24-09-2020
unsigned int CCodeLineCountModule::GetStatisticsResult() const
{
    return m_uiStatisticsResult;
}
