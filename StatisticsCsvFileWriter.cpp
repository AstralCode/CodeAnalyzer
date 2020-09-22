#include "StatisticsCsvFileWriter.h"

#include <fstream>

#include "ProgramStatusCodes.h"
#include "OSLayerHelper.h"
#include "StatisticsAnalyzerModule.h"

CStatisticsCsvFileWriter::CStatisticsCsvFileWriter( const std::filesystem::path& oOutputDirectoryPath, const char cSeparator ) :
	m_oOutputDirectoryPath{ oOutputDirectoryPath },
	m_cSeparator{ cSeparator }
{

}

void CStatisticsCsvFileWriter::SetSeparator( const char cSeparator )
{
	m_cSeparator = cSeparator;
}

int CStatisticsCsvFileWriter::WriteStatistics( const std::vector<std::reference_wrapper<const CStatisticsAnalyzerModule>>& oStatisticsAnalyzerModules )
{
	int iProgramStatusCode = EProgramStatusCodes::eSuccess;

	const std::filesystem::path oOutputFilenameString = PrepareOutputFilePath();
	std::ofstream oOutputFileStream{ oOutputFilenameString.u32string(), std::fstream::out | std::fstream::app };

	if ( oOutputFileStream.is_open() )
	{
		WriteStatisticsHeaders( oOutputFileStream, oStatisticsAnalyzerModules );
		WriteStatisticsResults( oOutputFileStream, oStatisticsAnalyzerModules );
	}
	else
	{
		iProgramStatusCode = EProgramStatusCodes::eOpenFileError;
	}

	return iProgramStatusCode;
}

void CStatisticsCsvFileWriter::WriteStatisticsHeaders( std::ofstream& oOutputFileStream, const std::vector<std::reference_wrapper<const CStatisticsAnalyzerModule>>& oStatisticsAnalyzerModules ) const
{
	for ( unsigned int uiIndex = 0u; uiIndex < oStatisticsAnalyzerModules.size(); ++uiIndex )
	{
		const CStatisticsAnalyzerModule& oModule = oStatisticsAnalyzerModules[uiIndex].get();
		oOutputFileStream << oModule.GetStatisticsHeader() << ( ( uiIndex + 1 < oStatisticsAnalyzerModules.size() ) ? m_cSeparator : '\n' );
	}
}

void CStatisticsCsvFileWriter::WriteStatisticsResults( std::ofstream& oOutputFileStream, const std::vector<std::reference_wrapper<const CStatisticsAnalyzerModule>>& oStatisticsAnalyzerModules ) const
{
	for ( unsigned int uiIndex = 0u; uiIndex < oStatisticsAnalyzerModules.size(); ++uiIndex )
	{
		const CStatisticsAnalyzerModule& oModule = oStatisticsAnalyzerModules[uiIndex].get();
		oOutputFileStream << oModule.GetStatisticsResult() << ( ( uiIndex + 1 < oStatisticsAnalyzerModules.size() ) ? m_cSeparator : '\n' );
	}
}

std::filesystem::path CStatisticsCsvFileWriter::PrepareOutputFilePath() const
{
	const std::string oCurrentDateString = COSLayerHelper::currentDate();

	std::string oCurrentTimeString = COSLayerHelper::currentTime();
	std::replace( oCurrentTimeString.begin(), oCurrentTimeString.end(), ':', '-' );

	return { m_oOutputDirectoryPath / ( "CodeAnalyzerStat--" + oCurrentDateString + "--" + oCurrentTimeString + ".csv" ) };
};
