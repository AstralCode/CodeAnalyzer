#include "CommandLineHandler.h"

#include <iostream>

#include "ProgramStatusCodes.h"

constexpr const char* USAGE_STR =
	"usage:" "\n"
	"\t"	"codeanalyzer.exe [input_directory_path] [output_directory_path]";

CCommandLineHandler::CCommandLineHandler( int iArgumentCount, char* apcArguments[] )
{
    for ( int iArgIndex = 1; iArgIndex < iArgumentCount; ++iArgIndex )
    {
        m_aArgumentStrings.push_back( apcArguments[iArgIndex] );
    }
}

int CCommandLineHandler::HandleArguments( std::filesystem::path& oInputDirectoryPath, std::filesystem::path& oOutputDirectoryPath ) const
{
	if ( m_aArgumentStrings.size() != 2 )
	{
		return EProgramStatusCodes::eIncorrectArgumentCount;
	}

	oInputDirectoryPath = m_aArgumentStrings[0];
	if ( !std::filesystem::exists( oInputDirectoryPath ) )
	{
		return EProgramStatusCodes::eIncorrectArgument;
	}

	oOutputDirectoryPath = m_aArgumentStrings[1];
	if ( !std::filesystem::exists( oOutputDirectoryPath ) )
	{
		return EProgramStatusCodes::eIncorrectArgument;
	}

    return EProgramStatusCodes::eSuccess;
}

void CCommandLineHandler::PrintUsage() const
{
	std::cerr << USAGE_STR << std::endl;
}
