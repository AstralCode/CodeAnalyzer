#include "CsvStatisticsReportWriter.h"

#include <fstream>

#include "ProgramStatusCodes.h"
#include "StatisticsCollection.h"
#include "DateTimeHelper.h"
#include "StringHelper.h"

// ^^x
// EProgramStatusCodes CCsvStatisticsReportWriter::CreateReport
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CCsvStatisticsReportWriter::CreateReport( const CStatisticsCollection& oStatisticsCollection, const std::filesystem::path& oOutputDirectoryPath, std::optional<std::string> oReportPrefixNameString, std::filesystem::path& oReportPath )
{
	EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

	oReportPath = PrepareOutputReportPath( oOutputDirectoryPath, oReportPrefixNameString );
	std::ofstream oFileStream{ oReportPath.string(), std::fstream::out };

	if ( oFileStream.is_open() )
	{
		if ( oReportPrefixNameString.has_value() )
		{
			oFileStream << ';';
		}
		
		WriteStatisticsHeaders( oFileStream, oStatisticsCollection );

		if ( oReportPrefixNameString.has_value() )
		{
			oFileStream << *oReportPrefixNameString << ';';
		}

		WriteStatisticsValues( oFileStream, oStatisticsCollection );
	}
	else
	{
		eStatus = EProgramStatusCodes::eOpenOutputFileError;
		oReportPath.clear();
	}

	return eStatus;
}

// ^^x
// void CCsvStatisticsReportWriter::WriteStatisticsHeaders
// 3BGO JIRA-238 24-09-2020
void CCsvStatisticsReportWriter::WriteStatisticsHeaders( std::ofstream& oFileStream, const CStatisticsCollection& oStatisticsCollection ) const
{
	const std::vector<SStatisticsResult> oStatisticsResultVector = oStatisticsCollection.GetStatisticsCollection();

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
void CCsvStatisticsReportWriter::WriteStatisticsValues( std::ofstream& oFileStream, const CStatisticsCollection& oStatisticsCollection ) const
{
	const std::vector<SStatisticsResult> oStatisticsResultVector = oStatisticsCollection.GetStatisticsCollection();

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
