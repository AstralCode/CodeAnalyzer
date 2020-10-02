#include "StatisticsAnalyzerModule.h"

// ^^x
// CStatisticsAnalyzerModule::CStatisticsAnalyzerModule
// 3BGO JIRA-238 02-10-2020
CStatisticsAnalyzerModule::CStatisticsAnalyzerModule( CCodeParser& oCodeParser ) :
	m_oCodeParser{ oCodeParser }
{

}

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
	m_oResultVector.push_back( { oHeaderString, 0u } );
}

// ^^x
// void CStatisticsAnalyzerModule::SetStatisticsResult
// 3BGO JIRA-238 02-10-2020
void CStatisticsAnalyzerModule::SetStatisticsResult( const unsigned int uiIndex, const unsigned int uiValue )
{
	m_oResultVector[uiIndex].uiValue = uiValue;
}

// ^^x
// void CStatisticsAnalyzerModule::AddStatisticsResult
// 3BGO JIRA-238 02-10-2020
void CStatisticsAnalyzerModule::AddStatisticsResult( const unsigned int uiIndex, const unsigned int uiValue )
{
	m_oResultVector[uiIndex].uiValue += uiValue;
}

// ^^x
// unsigned int CStatisticsAnalyzerModule::GetStatisticsResult
// 3BGO JIRA-238 02-10-2020
unsigned int CStatisticsAnalyzerModule::GetStatisticsResult( const unsigned int uiIndex ) const
{
	return m_oResultVector[uiIndex].uiValue;
}
