#pragma once

template<typename T>
struct SFindDataResult
{
	std::string oRegexMatchString;
	std::ptrdiff_t iRegexMatchPos{ 0 };
	T oData;

	friend bool operator<( const SFindDataResult<T> oLeft, const SFindDataResult<T> oRight )
	{
		return oLeft.oRegexMatchString < oRight.oRegexMatchString;
	}
};
