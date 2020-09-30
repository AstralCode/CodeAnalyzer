#include "SourceCodeFile.h"

#include <regex>

constexpr const char* CODE_FUNCTION_DATASET_REGEX_STR =
	R"(^[ \t]*((?:signed|unsigned[\s+])?[\w\d\_\t :<>,*&\n]+)\s+([\w\d\_:]+)::([\w\d\_]+)\(\s*([\w\d\_\t :<>,*&\/='";\n]*)\s*\)\s*((?:const)?)[ \t]*$)";

// ^^x
// CSourceCodeFile::CSourceCodeFile
// 3BGO JIRA-238 24-09-2020
CSourceCodeFile::CSourceCodeFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString ) :
	CCodeFile{ oFilePath, oFileContentString }
{

}

// ^^x
// std::vector<SFindMemberFunctionResult> CSourceCodeFile::FindMemberFunctions
// 3BGO JIRA-239 24-09-2020
std::vector<SFindMemberFunctionResult> CSourceCodeFile::FindMemberFunctions() const
{
	enum EMatchGroups
	{
		eEntireMatch,
		eReturnType,
		eClassName,
		eName,
		eArgList,
		eModifier
	};

	const int aiSubMatchGroups[] = { eEntireMatch, eReturnType, eClassName, eName, eArgList, eModifier };
	
	const std::regex oRegexPattern{ CODE_FUNCTION_DATASET_REGEX_STR };
	const std::string oCodeString = GetContent();

	std::vector<SFindMemberFunctionResult> oFindResultVector{};

	const std::sregex_token_iterator oRegexEndIt{};
	for ( std::sregex_token_iterator oRegexStartIt{oCodeString.cbegin(), oCodeString.cend(), oRegexPattern, aiSubMatchGroups }; oRegexStartIt != oRegexEndIt; ++oRegexStartIt )
	{
		SFindMemberFunctionResult oFindResult{};

		oFindResult.oMatchString = *oRegexStartIt++;
		oFindResult.oMemberFunctionDataset.oReturnTypeString = *oRegexStartIt++;
		oFindResult.oMemberFunctionDataset.oClassNameString = *oRegexStartIt++;
		oFindResult.oMemberFunctionDataset.oNameString = *oRegexStartIt++;
		oFindResult.oMemberFunctionDataset.oArgListString = *oRegexStartIt++;
		oFindResult.oMemberFunctionDataset.oModifierString = *oRegexStartIt;

		oFindResultVector.push_back( oFindResult );
	}

	return oFindResultVector;
}
