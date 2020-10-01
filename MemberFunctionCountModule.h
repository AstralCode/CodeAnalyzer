#pragma once

#include "StatisticsAnalyzerModule.h"

class CMemberFunctionCountModule final : public CStatisticsAnalyzerModule
{
public:
	CMemberFunctionCountModule();

	void OnStartProcess( const CCodeFile& oCodeFile ) override;

	void ProcessHeaderFile( const CHeaderCodeFile& oHeaderCodeFile ) override;
	void ProcessSourceFile( const CSourceCodeFile& oSourceCodeFile ) override;

	void OnEndProcess( const CCodeFile& oCodeFile ) override;

	std::string GetStatisticsHeader() const override;
	unsigned int GetStatisticsResult() const override;

private:
	unsigned int m_uiStatisticsResult;
};
