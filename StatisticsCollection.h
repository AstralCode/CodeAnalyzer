#pragma once

#include <map>
#include <vector>

#include "StatisticsTypes.h"
#include "StatisticsResult.h"

class CStatisticsCollection final
{
public:
	SStatisticsResult& operator[]( const EStatisticsTypes eType );

	std::vector<SStatisticsResult> GetStatisticsCollection() const;

private:
	std::map<EStatisticsTypes, SStatisticsResult> m_oStatisticsResultMap;
};
