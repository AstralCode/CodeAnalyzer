#pragma once

#include "StatisticsAnalyzerModule.h"

class CCodeLineCountModule final : public CStatisticsAnalyzerModule
{
public:
	CCodeLineCountModule();

	int ProcessLine( const std::string& oLine ) override;

	std::string GetStatisticsHeader() const override;
	unsigned int GetStatisticsResult() const override;

private:
	unsigned int m_uiStatisticsResult;
};
