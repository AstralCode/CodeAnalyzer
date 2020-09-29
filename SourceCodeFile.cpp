#include "SourceCodeFile.h"

#include <regex>

// ^^x
// CSourceCodeFile::CSourceCodeFile
// 3BGO JIRA-238 24-09-2020
CSourceCodeFile::CSourceCodeFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString ) :
	CCodeFile{ oFilePath, oFileContentString }
{

}

// ^^x
// std::vector<std::string> CSourceCodeFile::RetrieveCodeFunctionNames
// 3BGO JIRA-239 24-09-2020
std::vector<std::string> CSourceCodeFile::RetrieveCodeFunctionNames() const
{
	std::vector<std::string> oCodeFunctionDatasetVector{};

	const std::string oCodeString = GetContent();

	std::regex oRegexPattern{ R"(^[ \t]*(?:signed|unsigned[\s+])?[\w\d\_:<>*&]+\s+[\w\d\_:]+::[\w\d\_]+\((?:.*)\)(?:\s+const)?[ \t]*$)" };
	
	const std::sregex_token_iterator oRegexEndIt{};
	for ( std::sregex_token_iterator oRegexStartIt{ oCodeString.cbegin(), oCodeString.cend(), oRegexPattern };
		  oRegexStartIt != oRegexEndIt; ++oRegexStartIt )
	{
		oCodeFunctionDatasetVector.push_back( *oRegexStartIt );
	}

	return oCodeFunctionDatasetVector;
}
