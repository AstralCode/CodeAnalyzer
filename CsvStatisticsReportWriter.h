#pragma once

#include <filesystem>

#include "CodeAnalyzer.h"

class CCsvStatisticsReportWriter
{
public:
	EProgramStatusCodes CreateReport( const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oAnalyzerModuleVector, const SCommandLineArgumentDataset& oCommandLineArgumentDataset );

	CCsvStatisticsReportWriter( const CCsvStatisticsReportWriter& ) = delete;
	CCsvStatisticsReportWriter& operator=( const CCsvStatisticsReportWriter& ) = delete;

private:
	void WriteStatisticsHeaders( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oAnalyzerModuleVector, const char cDataSeparator ) const;
	void WriteStatisticsValues( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oAnalyzerModuleVector, const char cDataSeparator ) const;

	std::filesystem::path PrepareOutputFilePath( const std::filesystem::path& oOutputDirectoryPath, std::optional<std::string> oReportPrefixNameString ) const;
};
