#pragma once

#include <filesystem>

#include "CodeFile.h"

class CHeaderCodeFile;
class CSourceCodeFile;

class CStatisticsAnalyzerModule
{
public:
	CStatisticsAnalyzerModule() = default;
	virtual ~CStatisticsAnalyzerModule() = default;

	virtual void OnStartProcess( const CCodeFile& oCodeFile ) = 0;

	virtual void ProcessHeaderFile( const CHeaderCodeFile& oHeaderCodeFile ) = 0;
	virtual void ProcessSourceFile( const CSourceCodeFile& oSourceCodeFile ) = 0;

	virtual void OnEndProcess( const CCodeFile& oCodeFile ) = 0;

	virtual std::string GetStatisticsHeader() const = 0;
	virtual unsigned int GetStatisticsResult() const = 0;
};
