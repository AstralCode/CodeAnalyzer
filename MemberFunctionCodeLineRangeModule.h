#pragma once

#include <algorithm>

#include "StatisticsAnalyzerModule.h"

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

	Note: constructors and destructors are not included in the calculation,
	because they are not detected by regular expressions and therefore are not
	in the vector that stores all member functions

	Global functions (not members) are also not taken by regular expressions.
*/
class CMemberFunctionCodeLineRangeModule final : public CStatisticsAnalyzerModule
{
public:
	CMemberFunctionCodeLineRangeModule();

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile ) override;

private:
	template<typename T>
	bool IsValueContainsInRange( const T uiValue, const T uiMin, const T uiMax = std::numeric_limits<T>::max() ) const;
};

// ^^x
// inline bool CMemberFunctionCodeLineRangeModule::IsValueContainsInRange
// 3BGO JIRA-238 05-10-2020
template<typename T>
inline bool CMemberFunctionCodeLineRangeModule::IsValueContainsInRange( const T uiValue, const T uiMin, const T uiMax ) const
{
	return std::clamp( uiValue, uiMin, uiMax ) == uiValue;
}
