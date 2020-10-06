#pragma once

#include <algorithm>

#include "StatisticsAnalyzerModule.h"

/*
	### Module Description ###
	This module separately count the number of member functions lengths
	for different ranges. The line count ranges are:
	[0] ->   0 - 20,
	[1] ->  21 - 50,
	[2] ->  51 - 100,
	[3] -> 101 - 300,
	[4] -> 301 - more
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
// bool CMemberFunctionCodeLineRangeModule::IsValueContainsInRange
// 3BGO JIRA-238 05-10-2020
template<typename T>
bool CMemberFunctionCodeLineRangeModule::IsValueContainsInRange( const T uiValue, const T uiMin, const T uiMax ) const
{
	return std::clamp( uiValue, uiMin, uiMax ) == uiValue;
}
