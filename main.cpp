#include "ConsoleInterface.h"
#include "CommandLineHandler.h"
#include "CodeAnalyzer.h"
#include "CsvStatisticsReportWriter.h"
#include "CodeFileLineCountModule.h"
#include "MemberFunctionCountModule.h"
#include "MemberFunctionCodeLineRangeModule.h"
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
			const unsigned int uiCodeFileCount = CCodeAnalyzer::CountNumberCodeFiles( oCommandLineArgumentDataset.oInputDirectoryPath );
			oCodeAnalyzer.AddAnalyzerModule<CDeveloperAnalyzerModule>( *oCommandLineArgumentDataset.oDeveloperString, uiCodeFileCount );
		}
		else
		{
			oCodeAnalyzer.AddAnalyzerModule<CCodeFileLineCountModule>();
			oCodeAnalyzer.AddAnalyzerModule<CMemberFunctionCountModule>();
			oCodeAnalyzer.AddAnalyzerModule<CMemberFunctionCodeLineRangeModule>();
		}

		eStatus = oCodeAnalyzer.Execute( oCommandLineArgumentDataset );

		if ( eStatus == EProgramStatusCodes::eSuccess )
		{
			std::filesystem::path oOutputReportPath{};

			eStatus = oStatisticsReportWriter.CreateReport( oCodeAnalyzer.GetAnalyzerModules(), oCommandLineArgumentDataset, oOutputReportPath );

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
