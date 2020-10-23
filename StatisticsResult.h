#pragma once

#include <string>

struct SStatisticsResult
{
	using ValueType = std::size_t;

	std::string oHeaderString;
	ValueType uiValue{ 0u };
};
