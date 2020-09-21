#include "ProgramStatusCodes.h"
#include "CommandLineHandler.h"

int main( int iArgumentCount, char* apcArguments[] )
{
	CCommandLineHandler oCommandLineHandler{ iArgumentCount, apcArguments };

	std::filesystem::path oInputDirectoryPath;
	std::filesystem::path oOutputDirectoryPath;

	const int iProgramStatusCode = oCommandLineHandler.HandleArguments( oInputDirectoryPath,
																	    oOutputDirectoryPath );
	if ( iProgramStatusCode != EProgramStatusCodes::eSuccess )
	{
		oCommandLineHandler.PrintUsage();
	}

	return iProgramStatusCode;
}
