#include <iostream>

#include "CommandLineHandler.h"
#include "CodeAnalyzer.h"
#include "StatisticsCsvFileWriter.h"
#include "MemberFunctionCountModule.h"
#include "MemberFunctionLineCountModule.h"

// ^^x
// int main
// 3BGO JIRA-238 24-09-2020
// 3BGO JIRA-239 30-09-2020
int main( int iArgumentCount, char* apcArguments[] )
{
	CCommandLineHandler oCommandLineHandler{ iArgumentCount, apcArguments };

	std::filesystem::path oInputDirectoryPath{};
	std::filesystem::path oOutputDirectoryPath{};

	EProgramStatusCodes eStatus = oCommandLineHandler.HandleArguments( oInputDirectoryPath, oOutputDirectoryPath );

	if ( eStatus != EProgramStatusCodes::eSuccess )
	{
		std::cerr << oCommandLineHandler.GetUsageMessage() << '\n';
	}
	else
	{
		CCodeAnalyzer oCodeAnalyzer{};
		oCodeAnalyzer.AddModule<CMemberFunctionCountModule>();
		oCodeAnalyzer.AddModule<CMemberFunctionLineCountModule>();

		eStatus = oCodeAnalyzer.Execute( oInputDirectoryPath );

		if ( eStatus == EProgramStatusCodes::eSuccess )
		{
			CStatisticsCsvFileWriter oStatisticsFileWriter{};
			oStatisticsFileWriter.WriteFile( oCodeAnalyzer.GetModules(), oOutputDirectoryPath );
		}
	}

	return static_cast<int>( eStatus );
}
