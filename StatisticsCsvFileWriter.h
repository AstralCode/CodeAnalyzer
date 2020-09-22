#pragma once

#include <filesystem>

class CStatisticsAnalyzerModule;

class CStatisticsCsvFileWriter
{
public:
	CStatisticsCsvFileWriter( const std::filesystem::path& oOutputDirectoryPath, const char cSeparator = ',' );

	void SetSeparator( const char cSeparator );

	int WriteStatistics( const std::vector<std::reference_wrapper<const CStatisticsAnalyzerModule>>& oStatisticsAnalyzerModules );

private:
	void WriteStatisticsHeaders( std::ofstream& oOutputFileStream, const std::vector<std::reference_wrapper<const CStatisticsAnalyzerModule>>& oStatisticsAnalyzerModules ) const;
	void WriteStatisticsResults( std::ofstream& oOutputFileStream, const std::vector<std::reference_wrapper<const CStatisticsAnalyzerModule>>& oStatisticsAnalyzerModules ) const;

	std::filesystem::path PrepareOutputFilePath() const;

	std::filesystem::path m_oOutputDirectoryPath;

	char m_cSeparator;
};
