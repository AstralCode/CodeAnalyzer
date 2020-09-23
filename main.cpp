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

	int iProgramStatusCode = oCommandLineHandler.HandleArguments( oInputDirectoryPath, oOutputDirectoryPath );

	if ( iProgramStatusCode != static_cast<int>( EProgramStatusCodes::eSuccess ) )
	{
		std::cerr << oCommandLineHandler.GetUsageMessage() << '\n';
	}
	else
	{
		CCodeAnalyzer oCodeAnalyzer{};
		oCodeAnalyzer.AddModule<CCodeLineCountModule>();

		iProgramStatusCode = oCodeAnalyzer.Execute( oInputDirectoryPath );

		if ( iProgramStatusCode == static_cast<int>( EProgramStatusCodes::eSuccess ) )
		{
			CStatisticsCsvFileWriter oStatisticsFileWriter{ ';' };
			oStatisticsFileWriter.WriteStatistics( oCodeAnalyzer.GetModules(), oOutputDirectoryPath );
		}
	}

	return iProgramStatusCode;
}
