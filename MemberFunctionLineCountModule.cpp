#include "MemberFunctionLineCountModule.h"

#include <iostream>

#include "SourceCodeFile.h"

constexpr const char* MODULE_HEADER_STR = "Member function line count";

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
