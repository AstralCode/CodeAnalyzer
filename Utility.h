#pragma once

#include <algorithm>
#include <numeric>

struct SRange
{
	template<typename T>
	static constexpr bool Contains( const T oValue, const T oMin, const T oMax = std::numeric_limits<T>::max() );
};

// ^^x
// inline constexpr bool SRange::Contains
// 3BGO JIRA-238 13-10-2020
template<typename T>
inline constexpr bool SRange::Contains( const T oValue, const T oMin, const T oMax )
{
	return std::clamp( oValue, oMin, oMax ) == oValue;
}
