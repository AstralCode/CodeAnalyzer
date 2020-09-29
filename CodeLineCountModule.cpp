#include "CodeLineCountModule.h"

#include <iostream>

#include "SourceCodeFile.h"

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
void CCodeLineCountModule::OnStartProcess( const CCodeFile& )
{

}

// ^^x
// void CCodeLineCountModule::ProcessHeaderFile
// 3BGO JIRA-238 24-09-2020
void CCodeLineCountModule::ProcessHeaderFile( const CHeaderCodeFile& )
{

}

// ^^x
// void CCodeLineCountModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CCodeLineCountModule::ProcessSourceFile( const CSourceCodeFile& oSourceCodeFile )
{
    const std::vector<std::pair<std::string, CCodeFunctionDataset>> oFunctionDatasetVector = oSourceCodeFile.RetrieveCodeFunctionDataset();

    for ( const std::pair<std::string, CCodeFunctionDataset>& oFunctionDataset : oFunctionDatasetVector )
    {
        std::cout << "# MATCH #      = " << oFunctionDataset.first << std::endl;
        std::cout << "[ReturnType]   = " << oFunctionDataset.second.oReturnTypeString << std::endl;
        std::cout << "[ClassName]    = " << oFunctionDataset.second.oClassNameString << std::endl;
        std::cout << "[FunctionName] = " << oFunctionDataset.second.oFunctionNameString << std::endl;
        std::cout << "[FunctionArgs] = " << oFunctionDataset.second.oFunctionArgsString << std::endl;
    }
}

// ^^x
// void CCodeLineCountModule::OnEndProcess
// 3BGO JIRA-238 24-09-2020
void CCodeLineCountModule::OnEndProcess( const CCodeFile& )
{

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
