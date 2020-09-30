#include "SourceCodeFile.h"

#include <regex>

#include "StringHelper.h"

constexpr const char* CODE_FUNCTION_DATASET_REGEX_STR =
	R"((?:^[ \t]*\/\/\s*\^\^x\n[ \t]*\/\/.*\n[ \t]*\/\/\s*3([a-zA-Z_]{3})\s+([a-zA-Z0-9\_\-\.\(\) \t]+)\n(?:[\/\/a-zA-Z0-9\_\-\.\(\) \t\n]+)?)?^[ \t]*((?:signed|unsigned[\s+])?[\w\d\_\t :<>,*&\n]+)\s+([\w\d\_:]+)::([\w\d\_]+)\(\s*([\w\d\_\t :<>,*&\/='";\n]*)\s*\)\s*((?:const)?)[ \t]*$)";

// ^^x
// CSourceCodeFile::CSourceCodeFile
// 3BGO JIRA-238 24-09-2020
CSourceCodeFile::CSourceCodeFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString ) :
	CCodeFile{ oFilePath, oFileContentString }
{

}

// ^^x
// std::vector<SFindMemberFunctionHeaderResult> CSourceCodeFile::FindMemberFunctionHeaders
// 3BGO JIRA-239 24-09-2020
std::vector<SFindMemberFunctionHeaderResult> CSourceCodeFile::FindMemberFunctionHeaders() const
{
	enum EMatchGroups
	{
		eEntireMatch,
		eAuthor,
		eInfo,
		eReturnType,
		eClassName,
		eName,
		eArgList,
		eModifier
	};

	const int aiMatchGroups[] = { eEntireMatch, eAuthor, eInfo, eReturnType, eClassName, eName, eArgList, eModifier };
	
	const std::regex oRegexPattern{ CODE_FUNCTION_DATASET_REGEX_STR };
	const std::string oCodeString = GetContent();

	std::vector<SFindMemberFunctionHeaderResult> oResultVector{};

	const std::sregex_token_iterator oRegexEndIt{};
	for ( std::sregex_token_iterator oRegexBeginIt{ oCodeString.cbegin(), oCodeString.cend(), oRegexPattern, aiMatchGroups }; oRegexBeginIt != oRegexEndIt; ++oRegexBeginIt )
	{
		SFindMemberFunctionHeaderResult oResult{};

		oResult.oMatchString = *oRegexBeginIt++;

		oResult.oMemberFunctionHeaderDataset.oAuthorString = CStringHelper::SimplifyString( *oRegexBeginIt++ );
		oResult.oMemberFunctionHeaderDataset.oInfoString = CStringHelper::SimplifyString( *oRegexBeginIt++ );
		oResult.oMemberFunctionHeaderDataset.oReturnTypeString = CStringHelper::SimplifyString( *oRegexBeginIt++ );
		oResult.oMemberFunctionHeaderDataset.oClassNameString = CStringHelper::SimplifyString( *oRegexBeginIt++ );
		oResult.oMemberFunctionHeaderDataset.oNameString = CStringHelper::SimplifyString( *oRegexBeginIt++ );
		oResult.oMemberFunctionHeaderDataset.oArgListString = CStringHelper::SimplifyString( *oRegexBeginIt++ );
		oResult.oMemberFunctionHeaderDataset.oModifierString = CStringHelper::SimplifyString( *oRegexBeginIt );

		oResultVector.push_back( oResult );
	}

	return oResultVector;
}

// ^^x
// std::vector<SFindMemberFunctionBodyResult> CSourceCodeFile::FindMemberFunctionBodies
// 3BGO JIRA-239 30-09-2020
std::vector<SFindMemberFunctionBodyResult> CSourceCodeFile::FindMemberFunctionBodies() const
{
	return std::vector<SFindMemberFunctionBodyResult>();
}
