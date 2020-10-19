#include "CsvStatisticsReportWriter.h"

#include <fstream>

#include "ProgramStatusCodes.h"
#include "DateTimeHelper.h"
#include "StringHelper.h"

// ^^x
// EProgramStatusCodes CCsvStatisticsReportWriter::CreateReport
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CCsvStatisticsReportWriter::CreateReport( const std::vector<SStatisticsResult>& oStatisticsResultVector, const std::filesystem::path& oOutputDirectoryPath, std::optional<std::string> oReportPrefixNameString, std::filesystem::path& oOutputReportPath )
{
	EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

	oOutputReportPath = PrepareOutputReportPath( oOutputDirectoryPath, oReportPrefixNameString );
	
	std::ofstream oFileStream{ oOutputReportPath.string(), std::fstream::out };

	if ( oFileStream.is_open() )
	{
		oFileStream << ';';

		WriteStatisticsHeaders( oFileStream, oStatisticsResultVector );

		if ( oReportPrefixNameString.has_value() )
		{
			oFileStream << *oReportPrefixNameString;
		}

		oFileStream << ';';

		WriteStatisticsValues( oFileStream, oStatisticsResultVector );
	}
	else
	{
		eStatus = EProgramStatusCodes::eOpenOutputFileError;

		oOutputReportPath.clear();
	}

	return eStatus;
}

// ^^x
// void CCsvStatisticsReportWriter::WriteStatisticsHeaders
// 3BGO JIRA-238 24-09-2020
void CCsvStatisticsReportWriter::WriteStatisticsHeaders( std::ofstream& oFileStream, const std::vector<SStatisticsResult>& oStatisticsResultVector ) const
{
	for ( unsigned int uiResultIndex{ 0u }; uiResultIndex < oStatisticsResultVector.size(); ++uiResultIndex )
	{
		oFileStream << oStatisticsResultVector[uiResultIndex].oHeaderString;
			
		if ( uiResultIndex + 1 < oStatisticsResultVector.size() )
		{
			oFileStream << ';';
		}
		else
		{
			oFileStream << '\n';
		}
	}
}

// ^^x
// void CCsvStatisticsReportWriter::WriteStatisticsValues
// 3BGO JIRA-238 24-09-2020
void CCsvStatisticsReportWriter::WriteStatisticsValues( std::ofstream& oFileStream, const std::vector<SStatisticsResult>& oStatisticsResultVector ) const
{
	for ( unsigned int uiResultIndex{ 0u }; uiResultIndex < oStatisticsResultVector.size(); ++uiResultIndex )
	{
		oFileStream << oStatisticsResultVector[uiResultIndex].uiValue;

		if ( uiResultIndex + 1 < oStatisticsResultVector.size() )
		{
			oFileStream << ';';
		}
		else
		{
			oFileStream << '\n';
		}
	}
}

// ^^x
// std::filesystem::path CCsvStatisticsReportWriter::PrepareOutputReportPath
// 3BGO JIRA-238 24-09-2020
std::filesystem::path CCsvStatisticsReportWriter::PrepareOutputReportPath( const std::filesystem::path& oOutputDirectoryPath, std::optional<std::string> oReportPrefixNameString ) const
{
	const std::string oCurrentDateString = CDateTimeHelper::CurrentDate();
	const std::string oCurrentTimeString = CStringHelper::Replace( CDateTimeHelper::CurrentTime(), ':', '-' );

	std::string oFilenameString{ "CodeAnalyzerReport--" + oCurrentDateString + "--" + oCurrentTimeString + ".csv" };

	if ( oReportPrefixNameString.has_value() )
	{
		oFilenameString = *oReportPrefixNameString + "--" + oFilenameString;
	}

	return oOutputDirectoryPath / oFilenameString;
};
