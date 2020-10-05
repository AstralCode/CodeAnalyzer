#include "CommandLineHandler.h"

// ^^x
// CCommandLineHandler::CCommandLineHandler
// 3BGO JIRA-238 24-09-2020
CCommandLineHandler::CCommandLineHandler( int iArgumentCount, char* apcArguments[] )
{
	for ( int iArgIndex{ 1 }; iArgIndex < iArgumentCount; ++iArgIndex )
    {
        m_oArgumentVector.push_back( apcArguments[iArgIndex] );
    }
}

// ^^x
// EProgramStatusCodes CCommandLineHandler::HandleArguments
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CCommandLineHandler::HandleArguments( std::filesystem::path& oInputDirectoryPath, std::filesystem::path& oOutputDirectoryPath ) const
{
	if ( m_oArgumentVector.size() != 2u )
	{
		return EProgramStatusCodes::eIncorrectArgumentCount;
	}

	oInputDirectoryPath = m_oArgumentVector[0u];

	if ( !std::filesystem::exists( oInputDirectoryPath ) )
	{
		return EProgramStatusCodes::eIncorrectArgument;
	}

	oOutputDirectoryPath = m_oArgumentVector[1u];

	if ( !std::filesystem::exists( oOutputDirectoryPath ) )
	{
		return EProgramStatusCodes::eIncorrectArgument;
	}

    return EProgramStatusCodes::eSuccess;
}

// ^^x
// std::string CCommandLineHandler::GetUsageMessage
// 3BGO JIRA-238 24-09-2020
std::string CCommandLineHandler::GetUsageMessage() const
{
	return { "usage:" "\n\t" "codeanalyzer.exe [input_directory_path] [output_directory_path]" };
}
