#include "StatisticsCsvFileWriter.h"

#include <fstream>

#include "ProgramStatusCodes.h"
#include "OSLayerHelper.h"

CStatisticsCsvFileWriter::CStatisticsCsvFileWriter( const std::filesystem::path& oOutputDirectoryPath, const char cSeparator ) :
	m_oOutputDirectoryPath{ oOutputDirectoryPath },
	m_cSeparator{ cSeparator }
{

}

void CStatisticsCsvFileWriter::SetSeparator( const char cSeparator )
{
	m_cSeparator = cSeparator;
}

int CStatisticsCsvFileWriter::WriteStatistics( const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oStatisticsAnalyzerModules )
{
	int iProgramStatusCode = EProgramStatusCodes::eSuccess;

	const std::filesystem::path oFilenameString = PrepareOutputFilePath();
	std::ofstream oFileStream{ oFilenameString.string(), std::fstream::out | std::fstream::app };

	if ( oFileStream.is_open() )
	{
		WriteStatisticsHeaders( oFileStream, oStatisticsAnalyzerModules );
		WriteStatisticsResults( oFileStream, oStatisticsAnalyzerModules );

		oFileStream.close();
	}
	else
	{
		iProgramStatusCode = EProgramStatusCodes::eOpenFileError;
	}

	return iProgramStatusCode;
}

void CStatisticsCsvFileWriter::WriteStatisticsHeaders( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oStatisticsAnalyzerModules ) const
{
	for ( unsigned int uiIndex = 0u; uiIndex < oStatisticsAnalyzerModules.size(); ++uiIndex )
	{
		const CStatisticsAnalyzerModule& oModule = oStatisticsAnalyzerModules[uiIndex].get();
		oFileStream << oModule.GetStatisticsHeader() << ( ( uiIndex + 1 < oStatisticsAnalyzerModules.size() ) ? m_cSeparator : '\n' );
	}
}

void CStatisticsCsvFileWriter::WriteStatisticsResults( std::ofstream& oFileStream, const CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector& oStatisticsAnalyzerModules ) const
{
	for ( unsigned int uiIndex = 0u; uiIndex < oStatisticsAnalyzerModules.size(); ++uiIndex )
	{
		const CStatisticsAnalyzerModule& oModule = oStatisticsAnalyzerModules[uiIndex].get();
		oFileStream << oModule.GetStatisticsResult() << ( ( uiIndex + 1 < oStatisticsAnalyzerModules.size() ) ? m_cSeparator : '\n' );
	}
}

std::filesystem::path CStatisticsCsvFileWriter::PrepareOutputFilePath() const
{
	const std::string oCurrentDateString = COSLayerHelper::currentDate();

	std::string oCurrentTimeString = COSLayerHelper::currentTime();
	std::replace( oCurrentTimeString.begin(), oCurrentTimeString.end(), ':', '-' );

	return { m_oOutputDirectoryPath / ( "CodeAnalyzerStat--" + oCurrentDateString + "--" + oCurrentTimeString + ".csv" ) };
};
