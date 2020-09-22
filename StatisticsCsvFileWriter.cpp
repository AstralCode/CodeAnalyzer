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
	std::ofstream oOutputFile{ oOutputFilenameString.u32string(), std::fstream::out | std::fstream::app };

	if ( oOutputFile.is_open() )
	{
		for ( std::reference_wrapper<const CStatisticsAnalyzerModule> oStatisticsAnalyzerModule : oStatisticsAnalyzerModules )
		{
			const CStatisticsAnalyzerModule& oModule = oStatisticsAnalyzerModule.get();
			oOutputFile << oModule.GetStatisticsHeader() << m_cSeparator << oModule.GetStatisticsResult() << std::endl;
		}

		oOutputFile.close();
	}
	else
	{
		iProgramStatusCode = EProgramStatusCodes::eOpenFileError;
	}

	return iProgramStatusCode;
}

std::filesystem::path CStatisticsCsvFileWriter::PrepareOutputFilePath() const
{
	const std::string oCurrentDateString = COSLayerHelper::currentDate();

	std::string oCurrentTimeString = COSLayerHelper::currentTime();
	std::replace( oCurrentTimeString.begin(), oCurrentTimeString.end(), ':', '-' );

	return { m_oOutputDirectoryPath / ( "CodeAnalyzerStat--" + oCurrentDateString + "--" + oCurrentTimeString + ".csv" ) };
};
