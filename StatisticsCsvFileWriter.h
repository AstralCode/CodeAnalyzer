#pragma once

#include <filesystem>

#include "CodeAnalyzer.h"

class CStatisticsCsvFileWriter
{
public:
	EProgramStatusCodes WriteFile( const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oStatisticsAnalyzerModuleVector, const std::filesystem::path& oOutputDirectoryPath, const char cDataSeparator = ';' );

private:
	void WriteStatisticsHeaders( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oStatisticsAnalyzerModuleVector, const char cDataSeparator ) const;
	void WriteStatisticsValues( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oStatisticsAnalyzerModuleVector, const char cDataSeparator ) const;

	std::filesystem::path PrepareOutputFilePath( const std::filesystem::path& oOutputDirectoryPath ) const;
};
