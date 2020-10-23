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

	virtual void OnComplete();

	const std::vector<SStatisticsResult>& GetStatisticsResults() const;

protected:
	void CreateStatistics( const std::string& oHeaderString );
	SStatisticsResult& GetStatistics( const unsigned int uiIndex );

	std::size_t SumStatisticsValues() const;

	void ToPercent( const unsigned int uiStatisticsTargetIndex, const unsigned int eStatisticsInputIndex, const std::size_t uiTotalSumStatisticsValue );
	std::size_t CalculatePercent( const std::size_t uiStatisticsValue, const std::size_t uiTotalSumStatisticsValue ) const;

private:
	std::vector<SStatisticsResult> m_oResultVector;
};
