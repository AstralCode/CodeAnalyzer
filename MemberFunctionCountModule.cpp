#include "MemberFunctionCountModule.h"

#include <iostream>

#include "SourceCodeFile.h"

constexpr const char* MODULE_HEADER_STR = "Member function count";

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
    const std::vector<SFindMemberFunctionResult> oFindMemberFunctionResultVector = oSourceCodeFile.FindMemberFunctions();

    for ( const SFindMemberFunctionResult& oFindMemberFunctionResult : oFindMemberFunctionResultVector )
    {
        std::cout << "# MATCH #    = " << oFindMemberFunctionResult.oMatchString << '\n';
        std::cout << "[ReturnType] = " << oFindMemberFunctionResult.oMemberFunctionDataset.oReturnTypeString << '\n';
        std::cout << "[ClassName]  = " << oFindMemberFunctionResult.oMemberFunctionDataset.oClassNameString << '\n';
        std::cout << "[Name]       = " << oFindMemberFunctionResult.oMemberFunctionDataset.oNameString << '\n';
        std::cout << "[ArgList]    = " << oFindMemberFunctionResult.oMemberFunctionDataset.oArgListString << '\n';
        std::cout << "[Modifier]   = " << oFindMemberFunctionResult.oMemberFunctionDataset.oModifierString << '\n';
        std::cout << '\n';
    }

    m_uiStatisticsResult = oFindMemberFunctionResultVector.size();
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
