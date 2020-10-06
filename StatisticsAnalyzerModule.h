#pragma once

#include "CodeFile.h"

struct SStatisticsResult
{
	std::string oHeaderString;
	unsigned int uiValue{ 0u };
};

class CCodeParser;

class CStatisticsAnalyzerModule
{
public:
	CStatisticsAnalyzerModule( CCodeParser& oCodeParser );
	virtual ~CStatisticsAnalyzerModule() = default;

	CStatisticsAnalyzerModule( const CStatisticsAnalyzerModule& ) = delete;
	CStatisticsAnalyzerModule& operator=( const CStatisticsAnalyzerModule& ) = delete;

	virtual void ProcessCodeFile( const CCodeFile& oCodeFile ) = 0;

	virtual std::string GetModuleName() const = 0;

	std::vector<SStatisticsResult> GetStatisticsResults() const;

protected:
	CCodeParser& m_oCodeParser;

	void CreateStatistics( const std::string& oHeaderString );
	SStatisticsResult& GetStatistics( const unsigned int uiIndex );

private:
	std::vector<SStatisticsResult> m_oResultVector;
};
