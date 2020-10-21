#pragma once

#include <filesystem>
#include <optional>

#include "ProgramStatusCodes.h"
#include "StatisticsResult.h"

class CCsvStatisticsReportWriter
{
public:
	EProgramStatusCodes CreateReport( const std::vector<SStatisticsResult>& oStatisticsResultVector, const std::filesystem::path& oOutputDirectoryPath, std::optional<std::string> oReportPrefixNameString, std::filesystem::path& oReportPath );

	CCsvStatisticsReportWriter( const CCsvStatisticsReportWriter& ) = delete;
	CCsvStatisticsReportWriter& operator=( const CCsvStatisticsReportWriter& ) = delete;

private:
	void WriteStatisticsHeaders( std::ofstream& oFileStream, const std::vector<SStatisticsResult>& oStatisticsResultVector ) const;
	void WriteStatisticsValues( std::ofstream& oFileStream, const std::vector<SStatisticsResult>& oStatisticsResultVector ) const;

	std::filesystem::path PrepareOutputReportPath( const std::filesystem::path& oOutputDirectoryPath, std::optional<std::string> oReportPrefixNameString ) const;
};
