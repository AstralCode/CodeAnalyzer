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
		oCodeAnalyzer.AddAnalyzerModule<CCodeFileLineCountModule>();
		oCodeAnalyzer.AddAnalyzerModule<CMemberFunctionCountModule>();
		oCodeAnalyzer.AddAnalyzerModule<CMemberFunctionCodeLineRangeModule>();

		CConsoleInterface::PrintLine( "[" + CDateTimeHelper::CurrentTime() + "]: Code analysis in progress..." );

		eStatus = oCodeAnalyzer.Execute( oCommandLineArgumentDataset );

		if ( eStatus == EProgramStatusCodes::eSuccess )
		{
			CConsoleInterface::ClearLine();
			CConsoleInterface::PrintLine( "[" + CDateTimeHelper::CurrentTime() + "]: Analysis complete!" );

			std::filesystem::path oOutputReportPath{};

			eStatus = oStatisticsReportWriter.CreateReport( oCodeAnalyzer.GetAnalyzerModules(), oCommandLineArgumentDataset, oOutputReportPath );

			if ( eStatus == EProgramStatusCodes::eSuccess )
			{
				CConsoleInterface::PrintLine( "[" + CDateTimeHelper::CurrentTime() + "]: Report created at: \"" + oOutputReportPath.string() + "\"" );
			}
		}
	}

	return static_cast<int>( eStatus );
}
