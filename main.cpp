#include "ConsoleInterface.h"
#include "CommandLineHandler.h"
#include "CodeAnalyzer.h"
#include "StatisticsCsvFileWriter.h"
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
	CCommandLineHandler oCommandLineHandler{ iArgumentCount, apcArguments };
	CCodeAnalyzer oCodeAnalyzer{};
	CStatisticsCsvFileWriter oStatisticsFileWriter{};

	std::filesystem::path oInputDirectoryPath{};
	std::filesystem::path oOutputDirectoryPath{};

	EProgramStatusCodes eStatus = oCommandLineHandler.HandleArguments( oInputDirectoryPath, oOutputDirectoryPath );

	if ( eStatus != EProgramStatusCodes::eSuccess )
	{
		CConsoleInterface::PrintLine( oCommandLineHandler.GetUsageMessage() );
	}
	else
	{
		CConsoleInterface::PrintLine( "Output report directory: \"" + oOutputDirectoryPath.string() + "\"" );

		oCodeAnalyzer.AddModule<CCodeFileLineCountModule>();
		oCodeAnalyzer.AddModule<CMemberFunctionCountModule>();
		oCodeAnalyzer.AddModule<CMemberFunctionCodeLineRangeModule>();

		CConsoleInterface::NewLine();
		CConsoleInterface::PrintLine( "[" + CDateTimeHelper::CurrentTime() + "]: Code analysis in progress..." );

		eStatus = oCodeAnalyzer.Execute( oInputDirectoryPath );

		if ( eStatus == EProgramStatusCodes::eSuccess )
		{
			CConsoleInterface::ClearLine();
			CConsoleInterface::PrintLine( "[" + CDateTimeHelper::CurrentTime() + "]: Analysis Complete!" );

			eStatus = oStatisticsFileWriter.WriteFile( oCodeAnalyzer.GetModules(), oOutputDirectoryPath );

			if ( eStatus == EProgramStatusCodes::eSuccess )
			{
				CConsoleInterface::PrintLine( "Report has been created." );
			}
		}
	}

	return static_cast<int>( eStatus );
}
