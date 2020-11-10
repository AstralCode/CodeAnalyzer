#pragma once

#include <filesystem>
#include <optional>

#include "ProgramStatusCodes.h"

class CStatisticsCollection;

class CCsvStatisticsReportWriter final
{
public:
	EProgramStatusCodes CreateReport( const CStatisticsCollection& oStatisticsCollection, const std::filesystem::path& oOutputPath, std::optional<std::string> oReportPrefixNameString );

	CCsvStatisticsReportWriter( const CCsvStatisticsReportWriter& ) = delete;
	CCsvStatisticsReportWriter& operator=( const CCsvStatisticsReportWriter& ) = delete;

private:
	void WriteStatisticsHeaders( std::ofstream& oFileStream, const CStatisticsCollection& oStatisticsCollection ) const;
	void WriteStatisticsValues( std::ofstream& oFileStream, const CStatisticsCollection& oStatisticsCollection ) const;
};
