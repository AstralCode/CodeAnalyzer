#include "SourceCodeFile.h"

#include <regex>

constexpr const char* CODE_FUNCTION_DATASET_REGEX_STR =
	R"(^[ \t]*((?:signed|unsigned[\s+])?[\w\d\_ :<>,*&]+)\s+([\w\d\_:]+)::([\w\d\_]+)\((.*)\)\s*(?:const)?[ \t]*$)";

// ^^x
// CSourceCodeFile::CSourceCodeFile
// 3BGO JIRA-238 24-09-2020
CSourceCodeFile::CSourceCodeFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString ) :
	CCodeFile{ oFilePath, oFileContentString }
{

}

// ^^x
// std::vector<std::pair<std::string, CCodeFunctionDataset>> CSourceCodeFile::RetrieveCodeFunctionDataset
// 3BGO JIRA-239 24-09-2020
std::vector<std::pair<std::string, CCodeFunctionDataset>> CSourceCodeFile::RetrieveCodeFunctionDataset() const
{
	enum EMatchGroups
	{
		eEntireMatch,
		eReturnType,
		eClassName,
		eFunctionName,
		eFunctionArgs
	};

	const int aiSubMatches[] = { eEntireMatch, eReturnType, eClassName, eFunctionName, eFunctionArgs };
	
	const std::regex oRegexPattern{ CODE_FUNCTION_DATASET_REGEX_STR };
	const std::string oCodeString = GetContent();

	std::vector<std::pair<std::string, CCodeFunctionDataset>> oFunctionDatasetVector{};

	const std::sregex_token_iterator oRegexEndIt{};
	for ( std::sregex_token_iterator oRegexStartIt{oCodeString.cbegin(), oCodeString.cend(), oRegexPattern, aiSubMatches };
		  oRegexStartIt != oRegexEndIt; ++oRegexStartIt )
	{
		const std::string oMatchString = *oRegexStartIt++;

		CCodeFunctionDataset oFunctionDataset{};
		oFunctionDataset.oReturnTypeString = *oRegexStartIt++;
		oFunctionDataset.oClassNameString = *oRegexStartIt++;
		oFunctionDataset.oFunctionNameString = *oRegexStartIt++;
		oFunctionDataset.oFunctionArgsString = *oRegexStartIt;

		oFunctionDatasetVector.push_back( std::make_pair( oMatchString, oFunctionDataset ) );
	}

	return oFunctionDatasetVector;
}
