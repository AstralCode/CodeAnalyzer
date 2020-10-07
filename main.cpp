#include "ConsoleInterface.h"
#include "CommandLineHandler.h"
#include "CodeAnalyzer.h"
#include "CsvStatisticsReportWriter.h"
#include "CodeFileLineCountModule.h"
#include "MemberFunctionCountModule.h"
#include "MemberFunctionCodeLineRangeModule.h"

// ^^x
// int main
// 3BGO JIRA-238 24-09-2020
// 3BGO JIRA-239 30-09-2020
int main( int iArgumentCount, char* apcArguments[] )
{
	CCommandLineHandler oCommandLineHandler{ iArgumentCount, apcArguments };
	CCodeAnalyzer oCodeAnalyzer{};
	CCsvStatisticsReportWriter oStatisticsReportWriter{};

	SCommandLineArgumentDataset oCommandLineArgumentDataset{};
	EProgramStatusCodes eStatus = oCommandLineHandler.HandleArguments( oCommandLineArgumentDataset );

	if ( eStatus == EProgramStatusCodes::eSuccess )
	{
		oCodeAnalyzer.AddAnalyzerModule<CCodeFileLineCountModule>();
		oCodeAnalyzer.AddAnalyzerModule<CMemberFunctionCountModule>();
		oCodeAnalyzer.AddAnalyzerModule<CMemberFunctionCodeLineRangeModule>();

		CConsoleInterface::PrintLine( "Code analysis in progress...", true );

		eStatus = oCodeAnalyzer.Execute( oCommandLineArgumentDataset );

		if ( eStatus == EProgramStatusCodes::eSuccess )
		{
			CConsoleInterface::ClearLine();
			CConsoleInterface::PrintLine( "Analysis complete!", true );

			std::filesystem::path oOutputReportPath{};

			eStatus = oStatisticsReportWriter.CreateReport( oCodeAnalyzer.GetAnalyzerModules(), oCommandLineArgumentDataset, oOutputReportPath );

			if ( eStatus == EProgramStatusCodes::eSuccess )
			{
				CConsoleInterface::PrintLine( "Report created at: \"" + oOutputReportPath.string() + "\"", true );
			}
		}
	}
	else
	{
		CConsoleInterface::PrintLine( oCommandLineHandler.GetUsageMessage() );
	}

	return static_cast<int>( eStatus );
}
