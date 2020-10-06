#include "ConsoleInterface.h"
#include "CommandLineHandler.h"
#include "CodeAnalyzer.h"
#include "CsvStatisticsReportWriter.h"
#include "CodeFileLineCountModule.h"
#include "MemberFunctionCountModule.h"
#include "MemberFunctionCodeLineRangeModule.h"
#include "DateTimeHelper.h"

// ^^x
// int main
// 3BGO JIRA-238 24-09-2020
// 3BGO JIRA-239 30-09-2020
int main( int iArgumentCount, char* apcArguments[] )
{
	CCodeAnalyzer oCodeAnalyzer{};
	CCsvStatisticsReportWriter oStatisticsReportWriter{};

	CCommandLineHandler oCommandLineHandler{ iArgumentCount, apcArguments };

	SCommandLineArgumentDataset oCommandLineArgumentDataset{};
	EProgramStatusCodes eStatus = oCommandLineHandler.HandleArguments( oCommandLineArgumentDataset );

	if ( eStatus != EProgramStatusCodes::eSuccess )
	{
		CConsoleInterface::PrintLine( oCommandLineHandler.GetUsageMessage() );
	}
	else
	{
		CConsoleInterface::PrintLine( "Output report directory: \"" + oCommandLineArgumentDataset.oOutputDirectoryPath.string() + "\"" );

		oCodeAnalyzer.AddAnalyzerModule<CCodeFileLineCountModule>();
		oCodeAnalyzer.AddAnalyzerModule<CMemberFunctionCountModule>();
		oCodeAnalyzer.AddAnalyzerModule<CMemberFunctionCodeLineRangeModule>();

		CConsoleInterface::NewLine();
		CConsoleInterface::PrintLine( "[" + CDateTimeHelper::CurrentTime() + "]: Code analysis in progress..." );

		eStatus = oCodeAnalyzer.Execute( oCommandLineArgumentDataset );

		if ( eStatus == EProgramStatusCodes::eSuccess )
		{
			CConsoleInterface::ClearLine();
			CConsoleInterface::PrintLine( "[" + CDateTimeHelper::CurrentTime() + "]: Analysis Complete!" );

			eStatus = oStatisticsReportWriter.CreateReport( oCodeAnalyzer.GetAnalyzerModules(), oCommandLineArgumentDataset );

			if ( eStatus == EProgramStatusCodes::eSuccess )
			{
				CConsoleInterface::PrintLine( "Report has been created." );
			}
		}
	}

	return static_cast<int>( eStatus );
}
