#include "StatisticsCsvFileWriter.h"

#include <fstream>

#include "ProgramStatusCodes.h"
#include "DateTimeHelper.h"

// ^^x
// EProgramStatusCodes CStatisticsCsvFileWriter::WriteFile
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CStatisticsCsvFileWriter::WriteFile( const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oStatisticsAnalyzerModules, const std::filesystem::path& oOutputDirectoryPath, const char cDataSeparator/* = ';'*/ )
{
	EProgramStatusCodes eStatus = EProgramStatusCodes::eSuccess;

	const std::filesystem::path oFilenameString = PrepareOutputFilePath( oOutputDirectoryPath );
	std::ofstream oFileStream{ oFilenameString.string(), std::fstream::out | std::fstream::app };

	if ( oFileStream.is_open() )
	{
		WriteStatisticsHeaders( oFileStream, oStatisticsAnalyzerModules, cDataSeparator );
		WriteStatisticsValues( oFileStream, oStatisticsAnalyzerModules, cDataSeparator );
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
void CStatisticsCsvFileWriter::WriteStatisticsHeaders( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oStatisticsAnalyzerModuleVector, const char cDataSeparator ) const
{
	for ( unsigned int uiModuleIndex = 0u; uiModuleIndex < oStatisticsAnalyzerModuleVector.size(); ++uiModuleIndex )
	{
		const CStatisticsAnalyzerModule& oModule = oStatisticsAnalyzerModuleVector[uiModuleIndex].get();
		const std::vector<SStatisticsResult> oStatisticsResultsVector = oModule.GetStatisticsResults();

		for ( unsigned int uiResultIndex = 0u; uiResultIndex < oStatisticsResultsVector.size(); ++uiResultIndex )
		{
			oFileStream << oStatisticsResultsVector[uiResultIndex].oHeaderString;
			
			if ( uiResultIndex + 1 < oStatisticsResultsVector.size() )
			{
				oFileStream << cDataSeparator;
			}
		}

		oFileStream << ( ( uiModuleIndex + 1 < oStatisticsAnalyzerModuleVector.size() ) ? cDataSeparator : '\n' );
	}
}

// ^^x
// void CStatisticsCsvFileWriter::WriteStatisticsValues
// 3BGO JIRA-238 24-09-2020
void CStatisticsCsvFileWriter::WriteStatisticsValues( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oStatisticsAnalyzerModuleVector, const char cDataSeparator ) const
{
	for ( unsigned int uiModuleIndex = 0u; uiModuleIndex < oStatisticsAnalyzerModuleVector.size(); ++uiModuleIndex )
	{
		const CStatisticsAnalyzerModule& oModule = oStatisticsAnalyzerModuleVector[uiModuleIndex].get();
		const std::vector<SStatisticsResult> oStatisticsResultsVector = oModule.GetStatisticsResults();

		for ( unsigned int uiResultIndex = 0u; uiResultIndex < oStatisticsResultsVector.size(); ++uiResultIndex )
		{
			oFileStream << oStatisticsResultsVector[uiResultIndex].uiValue;

			if ( uiResultIndex + 1 < oStatisticsResultsVector.size() )
			{
				oFileStream << cDataSeparator;
			}
		}

		oFileStream << ( ( uiModuleIndex + 1 < oStatisticsAnalyzerModuleVector.size() ) ? cDataSeparator : '\n' );
	}
}

// ^^x
// std::filesystem::path CStatisticsCsvFileWriter::PrepareOutputFilePath
// 3BGO JIRA-238 24-09-2020
std::filesystem::path CStatisticsCsvFileWriter::PrepareOutputFilePath( const std::filesystem::path& oOutputDirectoryPath ) const
{
	const std::string oCurrentDateString = CDateTimeHelper::CurrentDate();

	std::string oCurrentTimeString = CDateTimeHelper::CurrentTime();
	std::replace( oCurrentTimeString.begin(), oCurrentTimeString.end(), ':', '-' );

	return { oOutputDirectoryPath / ( "CodeAnalyzerStat--" + oCurrentDateString + "--" + oCurrentTimeString + ".csv" ) };
};
