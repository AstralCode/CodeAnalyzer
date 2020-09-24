#include "SourceCodeFile.h"

#include <iostream>
#include <regex>

// ^^x
// CSourceCodeFile::CSourceCodeFile
// 3BGO JIRA-238 24-09-2020
CSourceCodeFile::CSourceCodeFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString ) :
	CCodeFile{ oFilePath, oFileContentString }
{

}

// ^^x
// std::vector<CodeFunctionDataset> CSourceCodeFile::RetrieveCodeFunctions
// 3BGO JIRA-239 24-09-2020
std::vector<CodeFunctionDataset> CSourceCodeFile::RetrieveCodeFunctions() const
{
	std::vector<CodeFunctionDataset> oCodeFunctionDatasetVector{};

	const std::string oCodeString = GetContent();

	std::regex oRegexPattern{ R"()" };
	std::smatch oRegexPatternMatch{};

	if ( std::regex_match( oCodeString, oRegexPatternMatch, oRegexPattern ) )
	{
		for ( const std::ssub_match& oMatchStrings : oRegexPatternMatch )
		{
			std::cout << oMatchStrings << std::endl;
		}
	}

	return oCodeFunctionDatasetVector;
}
