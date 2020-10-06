#pragma once

#include <filesystem>

#include "CodeAnalyzer.h"

class CStatisticsCsvFileWriter
{
public:
	EProgramStatusCodes WriteFile( const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oAnalyzerModuleVector, const SCommandLineArgumentDataset& oCommandLineArgumentDataset );

	CStatisticsCsvFileWriter( const CStatisticsCsvFileWriter& ) = delete;
	CStatisticsCsvFileWriter& operator=( const CStatisticsCsvFileWriter& ) = delete;

private:
	void WriteStatisticsHeaders( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oAnalyzerModuleVector, const char cDataSeparator ) const;
	void WriteStatisticsValues( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oAnalyzerModuleVector, const char cDataSeparator ) const;

	std::filesystem::path PrepareOutputFilePath( const std::filesystem::path& oOutputDirectoryPath, std::optional<std::string> oReportPrefixNameString ) const;
};
