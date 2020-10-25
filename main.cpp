#include "ConsoleInterface.h"
#include "CommandLineHandler.h"
#include "CodeAnalyzer.h"
#include "CsvStatisticsReportWriter.h"
#include "CodeLineCountModule.h"
#include "GlobalCountModule.h"
#include "FunctionCountModule.h"
#include "FunctionLengthModule.h"
#include "FunctionArgsCountModule.h"
#include "DialogUsesDatabaseModule.h"

// ^^x
// EProgramStatusCodes PrepareOutputDirectory
// 3BGO JIRA-238 23-10-2020
EProgramStatusCodes PrepareOutputDirectory( std::filesystem::path& oOutputDirectoryPath )
{
	EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

	oOutputDirectoryPath = std::filesystem::current_path().append( "Reports" );

	if ( !std::filesystem::exists( oOutputDirectoryPath ) )
	{
		std::filesystem::create_directories( oOutputDirectoryPath );
	}

	if ( !std::filesystem::exists( oOutputDirectoryPath ) )
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
			oCodeAnalyzer.AddAnalyzerModule<CFunctionArgsCountModule>();
			oCodeAnalyzer.AddAnalyzerModule<CDialogUsesDatabaseModule>();

			eStatus = oCodeAnalyzer.Execute( oCommandLineArgumentDataset.oInputDirectoryPath, oCommandLineArgumentDataset.oDeveloperString );
			if ( eStatus == EProgramStatusCodes::eSuccess )
			{
				std::filesystem::path oReportPath{};

				eStatus = oStatisticsReportWriter.CreateReport( oCodeAnalyzer.GetStatisticsCollection(), oOutputDirectoryPath, oCommandLineArgumentDataset.oReportPrefixNameString, oReportPath );
				if ( eStatus == EProgramStatusCodes::eSuccess )
				{
					CConsoleInterface::PrintLine( "Report created at: \"" + oReportPath.string() + "\"" );
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
