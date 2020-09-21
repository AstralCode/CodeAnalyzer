#pragma once

#include <string>

#include "ProgramStatusCodes.h"

class CStatisticsAnalyzerModule
{
public:
	CStatisticsAnalyzerModule() = default;
	virtual ~CStatisticsAnalyzerModule() = default;

	virtual int ProcessLine( const std::string& oLine ) = 0;

	virtual std::string GetStatisticsHeader() const = 0;
	virtual unsigned int GetStatisticsResult() const = 0;
};