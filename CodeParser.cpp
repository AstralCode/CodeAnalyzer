#include "CodeParser.h"

#include <regex>

#include "CodeFile.h"
#include "StringHelper.h"

constexpr const char* FIND_MEMBER_FUNCTION_HEADERS_REGEX_STR =
R"(^[ \t]*((?:signed|unsigned[\s+])?[\w\d\_\t :<>,*&\n]+)\s+([\w\d\_:]+)::([\w\d\_]+)\(\s*([\w\d\_\t :<>,*&\/='";\n]*)\s*\)\s*((?:const)?)[ \t]*$)";

constexpr const char* FIND_MEMBER_FUNCTION_HEADER_DETAILS_REGEX_STR =
R"((?:^[ \t]*\/\/\s*\^\^x\n[ \t]*\/\/.*\n[ \t]*\/\/\s*3([a-zA-Z_]{3})\s+([a-zA-Z0-9\_\-\.\(\) \t]+)\n(?:[\/\/a-zA-Z0-9\_\-\.\(\) \t\n]+)?)?^[ \t]*((?:signed|unsigned[\s+])?[\w\d\_\t :<>,*&\n]+)\s+([\w\d\_:]+)::([\w\d\_]+)\(\s*([\w\d\_\t :<>,*&\/='";\n]*)\s*\)\s*((?:const)?)[ \t]*$)";

constexpr const char* CHECK_FUNCTION_BRACKET_REGEX_STR =
R"([\{\}\s]{3})";

// ^^x
// std::vector<SFindMemberFunctionHeaderResult> CCodeParser::FindMemberFunctionHeaders
// 3BGO JIRA-238 02-10-2020
std::vector<SFindMemberFunctionHeaderResult> CCodeParser::FindMemberFunctionHeaders( const CCodeFile& oCodeFile ) const
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

	std::vector<SFindMemberFunctionHeaderDetailResult> oResultVector{};

	const int aiMatchGroups[] = {eEntireMatch, eAuthor, eInfo, eReturnType, eClassName, eName, eArgList, eModifier};

	const std::regex oRegexPattern{FIND_MEMBER_FUNCTION_HEADER_DETAILS_REGEX_STR};
	const std::string oCodeString = oCodeFile.GetContent();

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

// ^^x
// std::vector<SFindMemberFunctionBodyResult> CCodeParser::FindMemberFunctionBodies
// 3BGO JIRA-238 02-10-2020
std::vector<SFindMemberFunctionBodyResult> CCodeParser::FindMemberFunctionBodies( const CCodeFile& oCodeFile ) const
{
	std::vector<SFindMemberFunctionBodyResult> oResultVector{};

	const std::string& oCodeString = oCodeFile.GetContent();
	const std::vector<SFindMemberFunctionHeaderResult> oFindFunctionHeaderResultVector = FindMemberFunctionHeaders( oCodeFile );

	std::size_t uiFunctionBracketLevel = 0u;
	std::size_t uiFindOffsetPos = std::string::npos;

	for ( const SFindMemberFunctionHeaderResult& oFunctionHeaderResult : oFindFunctionHeaderResultVector )
	{
		SFindMemberFunctionBodyResult oResult{};

		oResult.oFunctionMatchString = oFunctionHeaderResult.oMatchString;

		const std::size_t uiMatchBegPos = oCodeString.find( oFunctionHeaderResult.oMatchString, ( uiFindOffsetPos != std::string::npos ) ? uiFindOffsetPos : 0u );
		const std::size_t uiMatchEndPos = uiMatchBegPos + oFunctionHeaderResult.oMatchString.size();

		const std::size_t uiFunctionBracketOpenPos = oCodeString.find_first_of( '{', uiMatchEndPos );
		uiFindOffsetPos = uiFunctionBracketOpenPos + 1u;

		if ( uiFunctionBracketOpenPos != std::string::npos )
		{
			uiFunctionBracketLevel = 1u;

			while ( uiFunctionBracketLevel > 0u )
			{
				const std::size_t uiFunctionLocalBracketPos = oCodeString.find_first_of( "{}", uiFindOffsetPos );

				if ( uiFunctionLocalBracketPos != std::string::npos )
				{
					const std::string oFunctionLocalBracketString = oCodeString.substr( uiFunctionLocalBracketPos - 1u, 3u );

					if ( std::regex_match( oFunctionLocalBracketString, std::regex( CHECK_FUNCTION_BRACKET_REGEX_STR ) ) )
					{
						if ( oCodeString[uiFunctionLocalBracketPos] == '{' )
						{
							++uiFunctionBracketLevel;
						}
						else
						{
							--uiFunctionBracketLevel;
						}
					}

					uiFindOffsetPos = uiFunctionLocalBracketPos + 1u;
				}
				else
				{
					break;
				}
			}

			if ( uiFunctionBracketLevel == 0u )
			{
				const std::size_t uiFunctionBracketClosePos = uiFindOffsetPos - uiFunctionBracketOpenPos;

				oResult.oFunctionBody = oCodeString.substr( uiFunctionBracketOpenPos, uiFunctionBracketClosePos );

				oResultVector.push_back( oResult );
			}
		}
	}

	return oResultVector;
}
