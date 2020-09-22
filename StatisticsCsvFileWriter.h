#pragma once

#include <filesystem>

#include "CodeAnalyzer.h"

class CStatisticsCsvFileWriter
{
public:
	CStatisticsCsvFileWriter( const std::filesystem::path& oOutputDirectoryPath, const char cSeparator = ',' );

	void SetSeparator( const char cSeparator );

	int WriteStatistics( const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oStatisticsAnalyzerModules );

private:
	void WriteStatisticsHeaders( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oStatisticsAnalyzerModules ) const;
	void WriteStatisticsResults( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oStatisticsAnalyzerModules ) const;

	std::filesystem::path PrepareOutputFilePath() const;

	std::filesystem::path m_oOutputDirectoryPath;

	char m_cSeparator;
};
