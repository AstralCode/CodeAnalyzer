#include "StatisticsCollection.h"

// ^^x
// SStatisticsResult& CStatisticsCollection::operator[]
// 3BGO JIRA-238 23-10-2020
SStatisticsResult& CStatisticsCollection::operator[]( const EStatisticsTypes eType )
{
	return m_oStatisticsResultMap[ eType ];
}

// ^^x
// std::vector<SStatisticsResult> CStatisticsCollection::GetStatisticsCollection
// 3BGO JIRA-238 23-10-2020
std::vector<SStatisticsResult> CStatisticsCollection::GetStatisticsCollection() const
{
	std::vector<SStatisticsResult> oStatisticsVector{};
	oStatisticsVector.reserve( m_oStatisticsResultMap.size() );

	for ( const std::pair<EStatisticsTypes, SStatisticsResult>& oStatisticsDataPair : m_oStatisticsResultMap )
	{
		oStatisticsVector.push_back( oStatisticsDataPair.second );
	}

	return oStatisticsVector;
}
