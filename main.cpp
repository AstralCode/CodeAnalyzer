#include <iostream>

#include "ProgramStatusCodes.h"
#include "CommandLineHandler.h"
#include "CodeAnalyzer.h"
#include "CodeLineCountModule.h"
#include "StatisticsCsvFileWriter.h"

int main( int iArgumentCount, char* apcArguments[] )
{
	CCommandLineHandler oCommandLineHandler{ iArgumentCount, apcArguments };

	std::filesystem::path oInputDirectoryPath{};
	std::filesystem::path oOutputDirectoryPath{};

	int iProgramStatusCode = oCommandLineHandler.HandleArguments( oInputDirectoryPath,
																  oOutputDirectoryPath );
	if ( iProgramStatusCode != EProgramStatusCodes::eSuccess )
	{
		std::cerr << oCommandLineHandler.GetUsageMessage() << '\n';
	}
	else
	{
		CCodeAnalyzer oCodeAnalyzer{ oInputDirectoryPath };
		oCodeAnalyzer.AddModule<CCodeLineCountModule>();

		iProgramStatusCode = oCodeAnalyzer.Execute();

		if ( iProgramStatusCode == EProgramStatusCodes::eSuccess )
		{
			CStatisticsCsvFileWriter oStatisticsFileWriter{ oOutputDirectoryPath, ';' };
			oStatisticsFileWriter.WriteStatistics( oCodeAnalyzer.GetModules() );
		}
	}

	return iProgramStatusCode;
}
