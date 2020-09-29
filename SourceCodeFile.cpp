#include "SourceCodeFile.h"

#include <regex>
#include <algorithm>

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
	std::vector<std::string> oFunctionNameVector{};

	const std::string oCodeString = GetContent();

	std::regex oRegexPattern{ R"(^[ \t]*(?:signed|unsigned[\s+])?[\w\d\_:<>*&]+\s+[\w\d\_:]+::[\w\d\_]+\((?:.*)\)(?:\s+const)?[ \t]*$)" };

	std::copy( std::sregex_token_iterator{ oCodeString.cbegin(), oCodeString.cend(), oRegexPattern },
			   std::sregex_token_iterator{},
			   std::back_inserter( oFunctionNameVector ) );

	return oFunctionNameVector;
}
