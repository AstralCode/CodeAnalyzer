#pragma once

#include "StatisticsAnalyzerModule.h"

/*
	### Module Description ####
	This module calculates the total number of member function
	in the source files.
*/
class CMemberFunctionCountModule final : public CStatisticsAnalyzerModule
{
public:
	CMemberFunctionCountModule();

	void OnStartProcessFile( const CCodeFile& oCodeFile ) override;

	void ProcessHeaderFile( const CHeaderCodeFile& oHeaderCodeFile ) override;
	void ProcessSourceFile( const CSourceCodeFile& oSourceCodeFile ) override;

	void OnEndProcessFile( const CCodeFile& oCodeFile ) override;

	std::string GetModuleName() const override;

	std::vector<SStatisticsResult> GetStatistics() const override;

private:
	unsigned int m_uiStatisticsResult;
};
