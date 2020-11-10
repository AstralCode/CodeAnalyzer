#include "CsvStatisticsReportWriter.h"

#include <fstream>

#include "ProgramStatusCodes.h"
#include "StatisticsCollection.h"

// ^^x
// EProgramStatusCodes CCsvStatisticsReportWriter::CreateReport
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CCsvStatisticsReportWriter::CreateReport( const CStatisticsCollection& oStatisticsCollection, const std::filesystem::path& oOutputPath, std::optional<std::string> oReportPrefixNameString )
{
	EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

	std::ofstream oFileStream{ oOutputPath.string(), std::fstream::out };

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
