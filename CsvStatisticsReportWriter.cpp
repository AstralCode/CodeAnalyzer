#include "CsvStatisticsReportWriter.h"

#include <fstream>

#include "ProgramStatusCodes.h"
#include "DateTimeHelper.h"
#include "StringHelper.h"

// ^^x
// EProgramStatusCodes CCsvStatisticsReportWriter::CreateReport
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CCsvStatisticsReportWriter::CreateReport( const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oAnalyzerModuleVector, const SCommandLineArgumentDataset& oCommandLineArgumentDataset, std::filesystem::path& oOutputReportPath )
{
	EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

	oOutputReportPath = PrepareOutputReportPath( oCommandLineArgumentDataset.oOutputDirectoryPath, oCommandLineArgumentDataset.oReportPrefixNameString );
	
	std::ofstream oFileStream{ oOutputReportPath.string(), std::fstream::out };
	char cDataSeparator{};

	if ( oFileStream.is_open() )
	{
		eStatus = AssignDataSeparator( oCommandLineArgumentDataset, cDataSeparator );

		WriteStatisticsHeaders( oFileStream, oAnalyzerModuleVector, cDataSeparator );
		WriteStatisticsValues( oFileStream, oAnalyzerModuleVector, cDataSeparator );
	}
	else
	{
		eStatus = EProgramStatusCodes::eOpenOutputFileError;

		oOutputReportPath.clear();
	}

	return eStatus;
}

// ^^x
// EProgramStatusCodes CCsvStatisticsReportWriter::AssignDataSeparator
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CCsvStatisticsReportWriter::AssignDataSeparator( const SCommandLineArgumentDataset& oCommandLineArgumentDataset, char& cDataSeparator ) const
{
	EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

	cDataSeparator = ';';

	if ( oCommandLineArgumentDataset.oReportDataSeparatorString.has_value() )
	{
		if ( oCommandLineArgumentDataset.oReportDataSeparatorString->size() == 1u )
		{
			cDataSeparator = ( *oCommandLineArgumentDataset.oReportDataSeparatorString )[0u];
		}
		else
		{
			eStatus = EProgramStatusCodes::eIncorrectDataSeparatorArgument;
		}
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
