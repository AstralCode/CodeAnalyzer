#pragma once

template<typename T>
struct SFindDataResult
{
	std::string oRegexMatchString;
	std::ptrdiff_t uiRegexMatchPos{0u};
	T oData;
};
