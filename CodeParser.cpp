#include "CodeParser.h"

#include <regex>

#include "CodeFile.h"
#include "StringHelper.h"

constexpr const char* FIND_MEMBER_FUNCTION_HEADERS_REGEX_STR =
R"(^[ \t]*((?:signed|unsigned[\s+])?[\w\d\_\t :<>,*&\n]+)\s+([\w\d\_:]+)::([\w\d\_]+)\(\s*([\w\d\_\t :<>,*&\/='";\n]*)\s*\)\s*((?:const)?)[ \t]*$)";

constexpr const char* FIND_MEMBER_FUNCTION_HEADER_DETAILS_REGEX_STR =
R"((?:^[ \t]*\/\/\s*\^\^x\n[ \t]*\/\/.*\n[ \t]*\/\/\s*3([a-zA-Z_]{3})\s+([a-zA-Z0-9\_\-\.\(\) \t]+)\n(?:[\/\/a-zA-Z0-9\_\-\.\(\) \t\n]+)?)?^[ \t]*((?:signed|unsigned[\s+])?[\w\d\_\t :<>,*&\n]+)\s+([\w\d\_:]+)::([\w\d\_]+)\(\s*([\w\d\_\t :<>,*&\/='";\n]*)\s*\)\s*((?:const)?)[ \t]*$)";

// ^^x
// std::vector<SFindMemberFunctionHeaderResult> CCodeParser::FindMemberFunctionHeader
// 3BGO JIRA-238 02-10-2020
std::vector<SFindMemberFunctionHeaderResult> CCodeParser::FindMemberFunctionHeader( const CCodeFile& oCodeFile ) const
{
	const std::regex oRegexPattern{FIND_MEMBER_FUNCTION_HEADERS_REGEX_STR};
	const std::string oCodeString = oCodeFile.GetContent();

	std::vector<SFindMemberFunctionHeaderResult> oResultVector{};

	const std::sregex_token_iterator oRegexEndIt{};
	for ( std::sregex_token_iterator oRegexBeginIt{ oCodeString.cbegin(), oCodeString.cend(), oRegexPattern }; oRegexBeginIt != oRegexEndIt; ++oRegexBeginIt )
	{
		SFindMemberFunctionHeaderResult oResult{};

		oResult.oMatchString = *oRegexBeginIt;

		oResultVector.push_back( oResult );
	}

	return oResultVector;
}

// ^^x
// std::vector<SFindMemberFunctionHeaderDetailResult> CCodeParser::FindMemberFunctionHeaderDetails
// 3BGO JIRA-238 02-10-2020
std::vector<SFindMemberFunctionHeaderDetailResult> CCodeParser::FindMemberFunctionHeaderDetails( const CCodeFile& oCodeFile ) const
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

	const int aiMatchGroups[] = {eEntireMatch, eAuthor, eInfo, eReturnType, eClassName, eName, eArgList, eModifier};

	const std::regex oRegexPattern{FIND_MEMBER_FUNCTION_HEADER_DETAILS_REGEX_STR};
	const std::string oCodeString = oCodeFile.GetContent();

	std::vector<SFindMemberFunctionHeaderDetailResult> oResultVector{};

	const std::sregex_token_iterator oRegexEndIt{};
	for ( std::sregex_token_iterator oRegexBeginIt{oCodeString.cbegin(), oCodeString.cend(), oRegexPattern, aiMatchGroups }; oRegexBeginIt != oRegexEndIt; ++oRegexBeginIt )
	{
		SFindMemberFunctionHeaderDetailResult oResult{};

		oResult.oMatchString = *oRegexBeginIt++;

		oResult.oMemberFunctionHeaderDataset.oAuthorString = CStringHelper::SimplifyString( *oRegexBeginIt++ );
		oResult.oMemberFunctionHeaderDataset.oInformationString = CStringHelper::SimplifyString( *oRegexBeginIt++ );
		oResult.oMemberFunctionHeaderDataset.oReturnTypeString = CStringHelper::SimplifyString( *oRegexBeginIt++ );
		oResult.oMemberFunctionHeaderDataset.oClassNameString = CStringHelper::SimplifyString( *oRegexBeginIt++ );
		oResult.oMemberFunctionHeaderDataset.oNameString = CStringHelper::SimplifyString( *oRegexBeginIt++ );
		oResult.oMemberFunctionHeaderDataset.oArgumentsString = CStringHelper::SimplifyString( *oRegexBeginIt++ );
		oResult.oMemberFunctionHeaderDataset.oModifierString = CStringHelper::SimplifyString( *oRegexBeginIt );

		oResultVector.push_back( oResult );
	}

	return oResultVector;
}
