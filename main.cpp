#include "ConsoleInterface.h"
#include "CommandLineHandler.h"
#include "CodeAnalyzer.h"
#include "CsvStatisticsReportWriter.h"
#include "CodeLineCountModule.h"
#include "FunctionCountModule.h"
#include "FunctionLengthModule.h"
#include "GlobalCountModule.h"

EProgramStatusCodes PrepareOutputDirectory( std::filesystem::path& oOutputDirectoryPath )
{
	EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

	oOutputDirectoryPath = std::filesystem::current_path().append( "Reports" );

	if ( !std::filesystem::exists( oOutputDirectoryPath ) )
	{
		std::filesystem::create_directories( oOutputDirectoryPath );
	}
	else
	{
		eStatus = EProgramStatusCodes::eCreateOutputDirectoryError;
	}

	return eStatus;
}

// ^^x
// int main
// 3BGO JIRA-238 24-09-2020
int main( int iArgumentCount, char* apcArguments[] )
{
	CCommandLineHandler oCommandLineHandler{ iArgumentCount, apcArguments };
	CCodeAnalyzer oCodeAnalyzer{};
	CCsvStatisticsReportWriter oStatisticsReportWriter{};

	SCommandLineArgumentDataset oCommandLineArgumentDataset{};
	EProgramStatusCodes eStatus = oCommandLineHandler.HandleArguments( oCommandLineArgumentDataset );

	if ( eStatus == EProgramStatusCodes::eSuccess )
	{
		std::filesystem::path oOutputDirectoryPath{};
		eStatus = PrepareOutputDirectory( oOutputDirectoryPath );

		if ( eStatus == EProgramStatusCodes::eSuccess )
		{
			oCodeAnalyzer.AddAnalyzerModule<CCodeLineCountModule>();
			oCodeAnalyzer.AddAnalyzerModule<CFunctionCountModule>();
			oCodeAnalyzer.AddAnalyzerModule<CGlobalCountModule>();
			oCodeAnalyzer.AddAnalyzerModule<CFunctionLengthModule>();

			eStatus = oCodeAnalyzer.Execute( oCommandLineArgumentDataset.oInputDirectoryPath, oCommandLineArgumentDataset.oDeveloperString );

			if ( eStatus == EProgramStatusCodes::eSuccess )
			{
				const std::size_t uiCodeFileCount = CCodeAnalyzer::CountNumberCodeFiles( oCommandLineArgumentDataset.oInputDirectoryPath );

				std::filesystem::path oReportPath{};

				std::vector<SStatisticsResult> oStatisticsResults = oCodeAnalyzer.GetStatisticsResults();
				oStatisticsResults.insert( oStatisticsResults.begin(), SStatisticsResult{ "Total Files", uiCodeFileCount } );

				eStatus = oStatisticsReportWriter.CreateReport( oStatisticsResults, oOutputDirectoryPath, oCommandLineArgumentDataset.oReportPrefixNameString, oReportPath );

				if ( eStatus == EProgramStatusCodes::eSuccess )
				{
					CConsoleInterface::PrintLineTime( "Report created at: \"" + oReportPath.string() + "\"" );
				}
			}
		}
	}
	else
	{
		CConsoleInterface::PrintLine( oCommandLineHandler.GetUsageMessage() );
	}

	return static_cast<int>( eStatus );
}
