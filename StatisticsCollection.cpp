#include "StatisticsCollection.h"

// ^^x
// void CStatisticsCollection::AddStatistics
// 3BGO NTP-1 11-01-2021
void CStatisticsCollection::AddStatistics( const EStatisticsTypes eType, const std::string_view oHeaderStringView, const SStatisticsResult::ValueType uiValue )
{
	m_oStatisticsResultMap.emplace( eType, SStatisticsResult{ oHeaderStringView.data(), uiValue } );
}

// ^^x
// void CStatisticsCollection::SetStatisticsValue
// 3BGO NTP-1 11-01-2021
void CStatisticsCollection::SetStatisticsValue( const EStatisticsTypes eType, const SStatisticsResult::ValueType uiValue )
{
	m_oStatisticsResultMap.at( eType ).uiValue = uiValue;
}

// ^^x
// SStatisticsResult::ValueType CStatisticsCollection::GetStatisticsValue
// 3BGO NTP-1 11-01-2021
SStatisticsResult::ValueType CStatisticsCollection::GetStatisticsValue( const EStatisticsTypes eType ) const
{
	return m_oStatisticsResultMap.at( eType ).uiValue;
}

// ^^x
// void CStatisticsCollection::AccumulateStatisticsValue
// 3BGO NTP-1 11-01-2021
void CStatisticsCollection::AccumulateStatisticsValue( const EStatisticsTypes eType, const SStatisticsResult::ValueType uiValue )
{
	std::map<EStatisticsTypes, SStatisticsResult>::iterator oStatisticsResultIt = m_oStatisticsResultMap.find( eType );
	if ( oStatisticsResultIt != m_oStatisticsResultMap.cend() )
	{
		oStatisticsResultIt->second.uiValue += uiValue;
	}
}

// ^^x
// void CStatisticsCollection::MergeStatistics
// 3BGO NTP-1 11-01-2021
void CStatisticsCollection::MergeStatistics( CStatisticsCollection& oStatisticsCollection )
{
	m_oStatisticsResultMap.merge( oStatisticsCollection.m_oStatisticsResultMap );
}

// ^^x
// std::vector<SStatisticsResult> CStatisticsCollection::GetStatisticsCollection
// 3BGO NTP-1 23-10-2020
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
