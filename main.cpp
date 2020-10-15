#include "ConsoleInterface.h"
#include "CommandLineHandler.h"
#include "CodeAnalyzer.h"
#include "CsvStatisticsReportWriter.h"
#include "CodeLineCountModule.h"
#include "FunctionCountModule.h"
#include "FunctionLengthModule.h"
#include "GlobalCountModule.h"
#include "DeveloperAnalyzerModule.h"

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
		if ( oCommandLineArgumentDataset.oDeveloperString.has_value() )
		{
			oCodeAnalyzer.AddAnalyzerModule<CDeveloperAnalyzerModule>( *oCommandLineArgumentDataset.oDeveloperString );
		}
		else
		{
			oCodeAnalyzer.AddAnalyzerModule<CCodeLineCountModule>();
			oCodeAnalyzer.AddAnalyzerModule<CFunctionCountModule>();
			oCodeAnalyzer.AddAnalyzerModule<CFunctionLengthModule>();
			oCodeAnalyzer.AddAnalyzerModule<CGlobalCountModule>();
		}

		eStatus = oCodeAnalyzer.Execute( oCommandLineArgumentDataset.oInputDirectoryPath );

		if ( eStatus == EProgramStatusCodes::eSuccess )
		{
			const unsigned int uiCodeFileCount = CCodeAnalyzer::CountNumberCodeFiles( oCommandLineArgumentDataset.oInputDirectoryPath );

			std::filesystem::path oOutputReportPath{};

			std::vector<SStatisticsResult> oStatisticsResults = oCodeAnalyzer.GetStatisticsResults();
			oStatisticsResults.insert( oStatisticsResults.begin(), SStatisticsResult{ "Files", uiCodeFileCount } );

			eStatus = oStatisticsReportWriter.CreateReport( oStatisticsResults, oCommandLineArgumentDataset.oOutputDirectoryPath, oCommandLineArgumentDataset.oReportPrefixNameString, oOutputReportPath );

			if ( eStatus == EProgramStatusCodes::eSuccess )
			{
				CConsoleInterface::PrintLineTime( "Report created at: \"" + oOutputReportPath.string() + "\"" );
			}
		}
	}
	else
	{
		CConsoleInterface::PrintLine( oCommandLineHandler.GetUsageMessage() );
	}

	return static_cast<int>( eStatus );
}
