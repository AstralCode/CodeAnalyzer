#include "CsvStatisticsReportWriter.h"

#include <fstream>

#include "ProgramStatusCodes.h"
#include "DateTimeHelper.h"
#include "StringHelper.h"

// ^^x
// EProgramStatusCodes CCsvStatisticsReportWriter::CreateReport
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CCsvStatisticsReportWriter::CreateReport( const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oAnalyzerModuleVector, const SCommandLineArgumentDataset& oCommandLineArgumentDataset )
{
	EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

	const std::filesystem::path oFilePathString = PrepareOutputFilePath( oCommandLineArgumentDataset.oOutputDirectoryPath, oCommandLineArgumentDataset.oReportPrefixNameString );
	std::ofstream oFileStream{ oFilePathString.string(), std::fstream::out };

	if ( oFileStream.is_open() )
	{
		char cDataSeparator{ ';' };

		if ( oCommandLineArgumentDataset.oReportDataSeparatorString.has_value() )
		{
			if ( oCommandLineArgumentDataset.oReportDataSeparatorString->size() == 1u )
			{
				cDataSeparator = ( *oCommandLineArgumentDataset.oReportDataSeparatorString )[0u];
			}
		}

		WriteStatisticsHeaders( oFileStream, oAnalyzerModuleVector, cDataSeparator );
		WriteStatisticsValues( oFileStream, oAnalyzerModuleVector, cDataSeparator );
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
void CCsvStatisticsReportWriter::WriteStatisticsHeaders( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oAnalyzerModuleVector, const char cDataSeparator ) const
{
	for ( unsigned int uiModuleIndex{ 0u }; uiModuleIndex < oAnalyzerModuleVector.size(); ++uiModuleIndex )
	{
		const CStatisticsAnalyzerModule& oAnalyzerModule = oAnalyzerModuleVector[uiModuleIndex].get();
		const std::vector<SStatisticsResult> oStatisticsResultVector = oAnalyzerModule.GetStatisticsResults();

		for ( unsigned int uiResultIndex{ 0u }; uiResultIndex < oStatisticsResultVector.size(); ++uiResultIndex )
		{
			oFileStream << oStatisticsResultVector[uiResultIndex].oHeaderString;
			
			if ( uiResultIndex + 1 < oStatisticsResultVector.size() )
			{
				oFileStream << cDataSeparator;
			}
		}

		oFileStream << ( ( uiModuleIndex + 1 < oAnalyzerModuleVector.size() ) ? cDataSeparator : '\n' );
	}
}

// ^^x
// void CCsvStatisticsReportWriter::WriteStatisticsValues
// 3BGO JIRA-238 24-09-2020
void CCsvStatisticsReportWriter::WriteStatisticsValues( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oAnalyzerModuleVector, const char cDataSeparator ) const
{
	for ( unsigned int uiModuleIndex{ 0u }; uiModuleIndex < oAnalyzerModuleVector.size(); ++uiModuleIndex )
	{
		const CStatisticsAnalyzerModule& oAnalyzerModule = oAnalyzerModuleVector[uiModuleIndex].get();
		const std::vector<SStatisticsResult> oStatisticsResultVector = oAnalyzerModule.GetStatisticsResults();

		for ( unsigned int uiResultIndex{ 0u }; uiResultIndex < oStatisticsResultVector.size(); ++uiResultIndex )
		{
			oFileStream << oStatisticsResultVector[uiResultIndex].uiValue;

			if ( uiResultIndex + 1 < oStatisticsResultVector.size() )
			{
				oFileStream << cDataSeparator;
			}
		}

		oFileStream << ( ( uiModuleIndex + 1 < oAnalyzerModuleVector.size() ) ? cDataSeparator : '\n' );
	}
}

// ^^x
// std::filesystem::path CCsvStatisticsReportWriter::PrepareOutputFilePath
// 3BGO JIRA-238 24-09-2020
std::filesystem::path CCsvStatisticsReportWriter::PrepareOutputFilePath( const std::filesystem::path& oOutputDirectoryPath, std::optional<std::string> oReportPrefixNameString ) const
{
	const std::string oCurrentDateString = CDateTimeHelper::CurrentDate();
	const std::string oCurrentTimeString = CStringHelper::Replace( CDateTimeHelper::CurrentTime(), ':', '-' );

	std::string oFilenameString{ "CodeAnalyzerRaport--" + oCurrentDateString + "--" + oCurrentTimeString + ".csv" };

	if ( oReportPrefixNameString.has_value() )
	{
		oFilenameString = *oReportPrefixNameString + "--" + oFilenameString;
	}

	return oOutputDirectoryPath / oFilenameString;
};
