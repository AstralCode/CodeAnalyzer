#pragma once

#include <filesystem>

#include "CodeFile.h"

class CHeaderCodeFile;
class CSourceCodeFile;

struct SStatisticsResult
{
	std::string oHeaderString{};
	unsigned int oValueString{};
};

class CStatisticsAnalyzerModule
{
public:
	CStatisticsAnalyzerModule() = default;
	virtual ~CStatisticsAnalyzerModule() = default;

	virtual void OnStartProcessFile( const CCodeFile& oCodeFile ) = 0;

	virtual void ProcessHeaderFile( const CHeaderCodeFile& oHeaderCodeFile ) = 0;
	virtual void ProcessSourceFile( const CSourceCodeFile& oSourceCodeFile ) = 0;

	virtual void OnEndProcessFile( const CCodeFile& oCodeFile ) = 0;

	virtual std::string GetModuleName() const = 0;

	virtual std::vector<SStatisticsResult> GetStatistics() const = 0;
};
