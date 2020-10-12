#include "StatisticsAnalyzerModule.h"

// ^^x
// std::vector<SStatisticsResult> CStatisticsAnalyzerModule::GetStatisticsResults
// 3BGO JIRA-238 02-10-2020
std::vector<SStatisticsResult> CStatisticsAnalyzerModule::GetStatisticsResults() const
{
	return m_oResultVector;
}

// ^^x
// void CStatisticsAnalyzerModule::CreateStatistics
// 3BGO JIRA-238 02-10-2020
void CStatisticsAnalyzerModule::CreateStatistics( const std::string& oHeaderString )
{
	m_oResultVector.push_back( { oHeaderString.data(), 0u } );
}

// ^^x
// SStatisticsResult& CStatisticsAnalyzerModule::GetStatistics
// 3BGO JIRA-238 02-10-2020
SStatisticsResult& CStatisticsAnalyzerModule::GetStatistics( const unsigned int uiIndex )
{
	return m_oResultVector[ uiIndex ];
}
