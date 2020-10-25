#pragma once

#include <filesystem>
#include <optional>

#include "ProgramStatusCodes.h"

class CStatisticsCollection;

class CCsvStatisticsReportWriter
{
public:
	EProgramStatusCodes CreateReport( const CStatisticsCollection& oStatisticsCollection, const std::filesystem::path& oOutputDirectoryPath, std::optional<std::string> oReportPrefixNameString, std::filesystem::path& oReportPath );

	CCsvStatisticsReportWriter( const CCsvStatisticsReportWriter& ) = delete;
	CCsvStatisticsReportWriter& operator=( const CCsvStatisticsReportWriter& ) = delete;

private:
	void WriteStatisticsHeaders( std::ofstream& oFileStream, const CStatisticsCollection& oStatisticsCollection ) const;
	void WriteStatisticsValues( std::ofstream& oFileStream, const CStatisticsCollection& oStatisticsCollection ) const;

	std::filesystem::path PrepareOutputReportPath( const std::filesystem::path& oOutputDirectoryPath, std::optional<std::string> oReportPrefixNameString ) const;
};
