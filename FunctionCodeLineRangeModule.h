#pragma once

#include <algorithm>

#include "StatisticsAnalyzerModule.h"
#include "Function.h"
#include "FindDataResult.h"

/*
	### Module Description ###
	This module separately count the number of member functions lengths
	for different ranges. The line count ranges are split by page length:
	[0] -> <0-16>		[QP]  -> Quarter page
	[1] -> <17-32>		[HP]  -> Half page
	[2] -> <33-62>		[1P]  -> 1 page
	[3] -> <63-124>		[2P]  -> 2 page
	[4] -> <125-248>	[4P]  -> 4 page
	[5] -> <249-more>	[4P+] -> 4 and more pages
*/
class CFunctionCodeLineRangeModule final : public CStatisticsAnalyzerModule
{
public:
	CFunctionCodeLineRangeModule();

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile ) override;

private:
	enum EStatisticsId
	{
		eFunctionQPLength,
		eFunctionHPLength,
		eFunction1PLength,
		eFunction2PLength,
		eFunction4PLength,
		eFunction4PMoreLength
	};

	void CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector );

	template<typename T>
	bool IsValueContainsInRange( const T uiValue, const T uiMin, const T uiMax = std::numeric_limits<T>::max() ) const;
};

// ^^x
// inline bool CFunctionCodeLineRangeModule::IsValueContainsInRange
// 3BGO JIRA-238 05-10-2020
template<typename T>
inline bool CFunctionCodeLineRangeModule::IsValueContainsInRange( const T uiValue, const T uiMin, const T uiMax ) const
{
	return std::clamp( uiValue, uiMin, uiMax ) == uiValue;
}
