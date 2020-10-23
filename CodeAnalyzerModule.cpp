#include "CodeAnalyzerModule.h"

// ^^x
// void CCodeAnalyzerModule::OnComplete
// 3BGO JIRA-238 22-10-2020
void CCodeAnalyzerModule::OnComplete()
{

}

// ^^x
// const std::vector<SStatisticsResult>& CCodeAnalyzerModule::GetStatisticsResults
// 3BGO JIRA-238 02-10-2020
const std::vector<SStatisticsResult>& CCodeAnalyzerModule::GetStatisticsResults() const
{
	return m_oResultVector;
}

// ^^x
// void CCodeAnalyzerModule::CreateStatistics
// 3BGO JIRA-238 02-10-2020
void CCodeAnalyzerModule::CreateStatistics( const std::string& oHeaderString )
{
	m_oResultVector.push_back( { oHeaderString, 0u } );
}

// ^^x
// SStatisticsResult& CCodeAnalyzerModule::GetStatistics
// 3BGO JIRA-238 02-10-2020
SStatisticsResult& CCodeAnalyzerModule::GetStatistics( const unsigned int uiIndex )
{
	return m_oResultVector[ uiIndex ];
}

// ^^x
// std::size_t CCodeAnalyzerModule::SumStatisticsValues
// 3BGO JIRA-238 24-09-2020
std::size_t CCodeAnalyzerModule::SumStatisticsValues() const
{
    std::size_t uiTotalSum{ 0u };

    const std::vector<SStatisticsResult>& oResults = GetStatisticsResults();
    for ( const SStatisticsResult& oResult : oResults )
    {
        uiTotalSum += oResult.uiValue;
    }

    return uiTotalSum;
}

// ^^x
// void CCodeAnalyzerModule::ToPercent
// 3BGO JIRA-238 24-09-2020
void CCodeAnalyzerModule::ToPercent( const unsigned int uiStatisticsTargetIndex, const unsigned int eStatisticsInputIndex, const std::size_t uiTotalSumStatisticsValue )
{
    GetStatistics( uiStatisticsTargetIndex ).uiValue = CalculatePercent( GetStatistics( eStatisticsInputIndex ).uiValue, uiTotalSumStatisticsValue );
}

// ^^x
// std::size_t CCodeAnalyzerModule::CalculatePercent
// 3BGO JIRA-238 24-09-2020
std::size_t CCodeAnalyzerModule::CalculatePercent( const std::size_t uiStatisticsValue, const std::size_t uiTotalSumStatisticsValue ) const
{
    return uiStatisticsValue * 100u / uiTotalSumStatisticsValue;
}
