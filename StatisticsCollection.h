#pragma once

#include <map>
#include <vector>

#include "StatisticsTypes.h"
#include "StatisticsResult.h"

class CStatisticsCollection final
{
public:
	void AddStatistics( const EStatisticsTypes eType, const std::string_view oHeaderStringView, const SStatisticsResult::ValueType uiValue = 0u );

	void SetStatisticsValue( const EStatisticsTypes eType, const SStatisticsResult::ValueType uiValue );
	SStatisticsResult::ValueType GetStatisticsValue( const EStatisticsTypes eType ) const;
	
	void AccumulateStatisticsValue( const EStatisticsTypes eType, const SStatisticsResult::ValueType uiValue );

	void MergeStatistics( CStatisticsCollection& oStatisticsCollection );

	std::vector<SStatisticsResult> GetStatisticsCollection() const;

private:
	std::map<EStatisticsTypes, SStatisticsResult> m_oStatisticsResultMap;
};
