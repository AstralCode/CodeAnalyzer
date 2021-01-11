#pragma once

#include <algorithm>
#include <numeric>
#include <thread>
#include <chrono>
#include <filesystem>

struct SRange
{
	template<typename T>
	static constexpr bool Contains( const T oValue, const T oMin, const T oMax = std::numeric_limits<T>::max() );
};

// ^^x
// inline constexpr bool SRange::Contains
// 3BGO NTP-1 13-10-2020
template<typename T>
inline constexpr bool SRange::Contains( const T oValue, const T oMin, const T oMax )
{
	return std::clamp( oValue, oMin, oMax ) == oValue;
}

// ^^x
// constexpr T ToPercent
// 3BGO NTP-1 23-10-2020
template<typename T>
constexpr T ToPercent( const T oValue, const T oTotal )
{
	T oResult{ 0 };

	if ( oTotal > static_cast< T >( 0 ) )
	{
		oResult = oValue * static_cast< T >( 100 ) / oTotal;
	}

	return oResult;
}

// ^^x
// void SleepThread
// 3BGO NTP-1 23-10-2020
inline void SleepThread( const unsigned long long ullSeconds )
{
	std::this_thread::sleep_for( std::chrono::seconds( ullSeconds ) );
}
