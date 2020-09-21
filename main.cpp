#include "ProgramStatusCodes.h"
#include "CommandLineHandler.h"
#include "CodeAnalyzer.h"
#include "CodeLineCountModule.h"

int main( int iArgumentCount, char* apcArguments[] )
{
	CCommandLineHandler oCommandLineHandler{ iArgumentCount, apcArguments };

	std::filesystem::path oInputDirectoryPath{};
	std::filesystem::path oOutputDirectoryPath{};

	int iProgramStatusCode = oCommandLineHandler.HandleArguments( oInputDirectoryPath,
																  oOutputDirectoryPath );
	if ( iProgramStatusCode != EProgramStatusCodes::eSuccess )
	{
		oCommandLineHandler.PrintUsage();
	}
	else
	{
		CCodeAnalyzer oCodeAnalyzer{ oInputDirectoryPath };
		oCodeAnalyzer.AddModule<CCodeLineCountModule>();

		iProgramStatusCode = oCodeAnalyzer.Execute();
	}

	return iProgramStatusCode;
}
