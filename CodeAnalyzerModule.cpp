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
