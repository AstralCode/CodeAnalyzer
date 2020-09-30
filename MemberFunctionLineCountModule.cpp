#include "MemberFunctionLineCountModule.h"

#include <iostream>

#include "SourceCodeFile.h"

constexpr const char* MODULE_HEADER_STR = "Function lines";

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
void CMemberFunctionLineCountModule::ProcessSourceFile( const CSourceCodeFile& oSourceCodeFile )
{
    const std::vector<SFindMemberFunctionHeaderResult> oFindMemberFunctionHeaderResultVector = oSourceCodeFile.FindMemberFunctionHeaders();

    for ( const SFindMemberFunctionHeaderResult& oFindMemberFunctionHeaderResult : oFindMemberFunctionHeaderResultVector )
    {
        std::cout << "# MATCH #    = " << oFindMemberFunctionHeaderResult.oMatchString << '\n';
        std::cout << "[Author]     = " << oFindMemberFunctionHeaderResult.oMemberFunctionHeaderDataset.oAuthorString << '\n';
        std::cout << "[Info]       = " << oFindMemberFunctionHeaderResult.oMemberFunctionHeaderDataset.oInfoString << '\n';
        std::cout << "[ReturnType] = " << oFindMemberFunctionHeaderResult.oMemberFunctionHeaderDataset.oReturnTypeString << '\n';
        std::cout << "[ClassName]  = " << oFindMemberFunctionHeaderResult.oMemberFunctionHeaderDataset.oClassNameString << '\n';
        std::cout << "[Name]       = " << oFindMemberFunctionHeaderResult.oMemberFunctionHeaderDataset.oNameString << '\n';
        std::cout << "[ArgList]    = " << oFindMemberFunctionHeaderResult.oMemberFunctionHeaderDataset.oArgListString << '\n';
        std::cout << "[Modifier]   = " << oFindMemberFunctionHeaderResult.oMemberFunctionHeaderDataset.oModifierString << '\n';
        std::cout << '\n';
    }
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
