#pragma once

#include <string>
#include <vector>

#include "StatisticsResult.h"

class CHeaderFile;
class CSourceFile;

class CStatisticsAnalyzerModule
{
public:
	CStatisticsAnalyzerModule() = default;
	virtual ~CStatisticsAnalyzerModule() = default;

	CStatisticsAnalyzerModule( const CStatisticsAnalyzerModule& ) = delete;
	CStatisticsAnalyzerModule& operator=( const CStatisticsAnalyzerModule& ) = delete;

	virtual void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) = 0;
	virtual void ProcessSourceFile( const CSourceFile& oSourceFile ) = 0;

	std::vector<SStatisticsResult> GetStatisticsResults() const;

protected:
	void CreateStatistics( std::string_view oHeaderString );
	SStatisticsResult& GetStatistics( const unsigned int uiIndex );

private:
	std::vector<SStatisticsResult> m_oResultVector;
};
