#include "MemberFunctionLineCountRangeModule.h"

#include "SourceCodeFile.h"

// ^^x
// CMemberFunctionLineCountRangeModule::CMemberFunctionLineCountRangeModule
// 3BGO JIRA-239 30-09-2020
CMemberFunctionLineCountRangeModule::CMemberFunctionLineCountRangeModule() :
    m_uiStatisticsResult{ 0u }
{

}

// ^^x
// void CMemberFunctionLineCountRangeModule::OnStartProcessFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionLineCountRangeModule::OnStartProcessFile( const CCodeFile& )
{

}

// ^^x
// void CMemberFunctionLineCountRangeModule::ProcessHeaderFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionLineCountRangeModule::ProcessHeaderFile( const CHeaderCodeFile& )
{

}

// ^^x
// void CMemberFunctionLineCountRangeModule::ProcessSourceFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionLineCountRangeModule::ProcessSourceFile( const CSourceCodeFile& oSourceCodeFile )
{
    m_uiStatisticsResult += oSourceCodeFile.FindMemberFunctionHeader().size();
}

// ^^x
// void CMemberFunctionLineCountRangeModule::OnEndProcessFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionLineCountRangeModule::OnEndProcessFile( const CCodeFile& )
{

}

// ^^x
// std::string CMemberFunctionLineCountRangeModule::GetModuleName
// 3BGO JIRA-238 01-10-2020
std::string CMemberFunctionLineCountRangeModule::GetModuleName() const
{
    return "Function Line Range Counter";
}

// ^^x
// std::vector<SStatisticsResult> CMemberFunctionLineCountRangeModule::GetStatistics
// 3BGO JIRA-238 24-09-2020
std::vector<SStatisticsResult> CMemberFunctionLineCountRangeModule::GetStatistics() const
{
    return
    {
        { "Function Line Count [0-20]", m_uiStatisticsResult },
        { "Function Line Count [21-50]", 450u },
        { "Function Line Count [51-100]", 250u },
        { "Function Line Count [101-300]", 20u }
    };
}
