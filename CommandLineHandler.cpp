#include "CommandLineHandler.h"

#include <regex>

#include "StringHelper.h"

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
EProgramStatusCodes CCommandLineHandler::HandleArguments( SCommandLineArgumentDataset& oArgumentDataset ) const
{
	EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

	if ( m_oArgumentVector.size() < 1u )
	{
		eStatus = EProgramStatusCodes::eIncorrectArgumentCount;
	}

	if ( eStatus == EProgramStatusCodes::eSuccess )
	{
		eStatus = HandleRequiredArguments( oArgumentDataset );

		if ( eStatus == EProgramStatusCodes::eSuccess )
		{
			eStatus = HandleOptionalArguments( oArgumentDataset );
		}
	}

    return eStatus;
}

// ^^x
// std::string CCommandLineHandler::GetUsageMessage
// 3BGO JIRA-238 24-09-2020
std::string CCommandLineHandler::GetUsageMessage() const
{
	return {
		"usage:" "\n\t"
			"codeanalyzer.exe <input_directory_path>" "\n\n"
		"optional options:" "\n\t"
			"[--report-prefix]" };
}

// ^^x
// EProgramStatusCodes CCommandLineHandler::HandleRequiredArguments
// 3BGO JIRA-238 06-10-2020
EProgramStatusCodes CCommandLineHandler::HandleRequiredArguments( SCommandLineArgumentDataset& oArgumentDataset ) const
{
	EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

	const std::filesystem::path oInputDirectoryPath{ m_oArgumentVector[0] };

	if ( std::filesystem::exists( oInputDirectoryPath ) && std::filesystem::is_directory( oInputDirectoryPath ) )
	{
		oArgumentDataset.oInputDirectoryPath = oInputDirectoryPath;
	}
	else
	{
		eStatus = EProgramStatusCodes::eIncorrectInputDirectoryArgument;
	}

	return eStatus;
}

// ^^x
// EProgramStatusCodes CCommandLineHandler::HandleOptionalArguments
// 3BGO JIRA-238 06-10-2020
EProgramStatusCodes CCommandLineHandler::HandleOptionalArguments( SCommandLineArgumentDataset& oArgumentDataset ) const
{
	EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

	for ( unsigned int uiArgIndex{ 2u }; uiArgIndex + 1u < m_oArgumentVector.size(); uiArgIndex += 2u )
	{
		const std::string& oInputString = m_oArgumentVector[uiArgIndex + 0u] + " " + m_oArgumentVector[uiArgIndex + 1u];

		std::smatch oMatchRegex{};
		
		if ( std::regex_match( oInputString, oMatchRegex, std::regex{ R"(\-\-(\w+(?:\-\w+)*)\s+(.+))" } ) )
		{
			HandleOptionalArgument( oArgumentDataset, oMatchRegex[1u].str(), oMatchRegex[2u].str() );
		}
	}

	return eStatus;
}

// ^^x
// EProgramStatusCodes CCommandLineHandler::HandleOptionalArgument
// 3BGO JIRA-238 06-10-2020
EProgramStatusCodes CCommandLineHandler::HandleOptionalArgument( SCommandLineArgumentDataset& oArgumentDataset, const std::string& oOptionString, const std::string& oArgumentString ) const
{
	EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

	const std::string oOptionLowerCaseString = CStringHelper::ToLowerCase( oOptionString );

	if ( oOptionLowerCaseString == "report-prefix" )
	{
		AssignOptionalArgument( oArgumentDataset.oReportPrefixNameString, oArgumentString );
	}
	else if ( oOptionLowerCaseString == "dev" )
	{
		AssignOptionalArgument( oArgumentDataset.oDeveloperString, oArgumentString );
	}
	else
	{
		eStatus = EProgramStatusCodes::eIncorrectOptionArgument;
	}

	return eStatus;
}

// ^^x
// void CCommandLineHandler::AssignOptionalArgument
// 3BGO JIRA-238 09-10-2020
void CCommandLineHandler::AssignOptionalArgument( std::optional<std::string>& oOutputString, const std::string& oArgumentString ) const
{
	if ( !oOutputString.has_value() )
	{
		oOutputString = oArgumentString;
	}
}
