#pragma once

#include "CodeFile.h"

struct SStatisticsResult
{
	std::string oHeaderString{};
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

	virtual void PreProcessCodeFile( const CCodeFile& oCodeFile ) = 0;
	virtual void ProcessCodeFile( const CCodeFile& oCodeFile ) = 0;
	virtual void PostProcessCodeFile( const CCodeFile& oCodeFile ) = 0;

	virtual std::string GetModuleName() const = 0;

	std::vector<SStatisticsResult> GetStatisticsResults() const;

protected:
	CCodeParser& m_oCodeParser;

	void CreateStatistics( const std::string& oHeaderString );
	void SetStatisticsResult( const unsigned int uiIndex, const unsigned int uiValue );
	void AddStatisticsResult( const unsigned int uiIndex, const unsigned int uiValue );
	unsigned int GetStatisticsResult( const unsigned int uiIndex ) const;

private:
	std::vector<SStatisticsResult> m_oResultVector;
};
