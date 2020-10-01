#pragma once

#include "StatisticsAnalyzerModule.h"

/*
	### Module Description ###
	This module separately count the number of member functions lengths
	for different ranges. The line count ranges are:
	[0] ->   0 - 20,
	[1] ->  21 - 50,
	[2] ->  51 - 100,
	[3] -> 101 - 300,
	[4] -> 301 - more
*/
class CMemberFunctionLineCountRangeModule final : public CStatisticsAnalyzerModule
{
public:
	CMemberFunctionLineCountRangeModule();

	void OnStartProcess( const CCodeFile& oCodeFile ) override;

	void ProcessHeaderFile( const CHeaderCodeFile& oHeaderCodeFile ) override;
	void ProcessSourceFile( const CSourceCodeFile& oSourceCodeFile ) override;

	void OnEndProcess( const CCodeFile& oCodeFile ) override;

	std::string GetModuleName() const override;

	std::vector<SStatisticsResult> GetStatistics() const override;

private:
	unsigned int m_uiStatisticsResult;
};
