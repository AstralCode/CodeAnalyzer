#pragma once

#include "StatisticsAnalyzerModule.h"

class CCodeLineCountModule final : public CStatisticsAnalyzerModule
{
public:
	CCodeLineCountModule();

	void OnStartProcess( const CCodeFile& oCodeFile ) override;

	void ProcessHeaderFile( const CHeaderCodeFile& oHeaderCodeFile ) override;
	void ProcessSourceFile( const CSourceCodeFile& oSourceCodeFile ) override;

	void OnEndProcess( const CCodeFile& oCodeFile ) override;

	std::string GetStatisticsHeader() const override;
	unsigned int GetStatisticsResult() const override;

private:
	unsigned int m_uiStatisticsResult;
};
