#pragma once

#include <string>
#include <vector>

#include "StatisticsResult.h"

class CHeaderFile;
class CSourceFile;

class CCodeAnalyzerModule
{
public:
	CCodeAnalyzerModule() = default;
	virtual ~CCodeAnalyzerModule() = default;

	CCodeAnalyzerModule( const CCodeAnalyzerModule& ) = delete;
	CCodeAnalyzerModule& operator=( const CCodeAnalyzerModule& ) = delete;

	virtual void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) = 0;
	virtual void ProcessSourceFile( const CSourceFile& oSourceFile ) = 0;

	std::vector<SStatisticsResult> GetStatisticsResults() const;

protected:
	void CreateStatistics( const std::string& oHeaderString );
	SStatisticsResult& GetStatistics( const unsigned int uiIndex );

private:
	std::vector<SStatisticsResult> m_oResultVector;
};
