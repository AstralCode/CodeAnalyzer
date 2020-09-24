#include "CommandLineHandler.h"

constexpr const char* USAGE_STR =
	"usage:" "\n"
	"\t"	"codeanalyzer.exe [input_directory_path] [output_directory_path]";

// ^^x
// CCommandLineHandler::CCommandLineHandler
// 3BGO JIRA-238 24-09-2020
CCommandLineHandler::CCommandLineHandler( int iArgumentCount, char* apcArguments[] )
{
    for ( unsigned int uiArgIndex = 1u; uiArgIndex < iArgumentCount; ++uiArgIndex )
    {
        m_oArgumentVector.push_back( apcArguments[uiArgIndex] );
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
	return USAGE_STR;
}
