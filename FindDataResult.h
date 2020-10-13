#pragma once

template<typename T>
struct SFindDataResult
{
	std::string oRegexMatchString;
	std::ptrdiff_t iRegexMatchPos{ 0 };
	T oData;
};
