#include "StatisticsCsvFileWriter.h"

#include <fstream>

#include "ProgramStatusCodes.h"
#include "DateTimeHelper.h"
#include "StringHelper.h"

// ^^x
// EProgramStatusCodes CStatisticsCsvFileWriter::WriteFile
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CStatisticsCsvFileWriter::WriteFile( const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oAnalyzerModuleVector, const SCommandLineArgumentDataset& oCommandLineArgumentDataset )
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
// void CStatisticsCsvFileWriter::WriteStatisticsHeaders
// 3BGO JIRA-238 24-09-2020
void CStatisticsCsvFileWriter::WriteStatisticsHeaders( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oAnalyzerModuleVector, const char cDataSeparator ) const
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
// void CStatisticsCsvFileWriter::WriteStatisticsValues
// 3BGO JIRA-238 24-09-2020
void CStatisticsCsvFileWriter::WriteStatisticsValues( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oAnalyzerModuleVector, const char cDataSeparator ) const
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
// std::filesystem::path CStatisticsCsvFileWriter::PrepareOutputFilePath
// 3BGO JIRA-238 24-09-2020
std::filesystem::path CStatisticsCsvFileWriter::PrepareOutputFilePath( const std::filesystem::path& oOutputDirectoryPath, std::optional<std::string> oReportPrefixNameString ) const
{
	const std::string oCurrentDateString = CDateTimeHelper::CurrentDate();
	const std::string oCurrentTimeString = CStringHelper::Replace( CDateTimeHelper::CurrentTime(), ':', '-' );

	std::string oFilenameString{ "CodeAnalyzerStat--" + oCurrentDateString + "--" + oCurrentTimeString + ".csv" };

	if ( oReportPrefixNameString.has_value() )
	{
		oFilenameString = *oReportPrefixNameString + "--" + oFilenameString;
	}

	return oOutputDirectoryPath / oFilenameString;
};
