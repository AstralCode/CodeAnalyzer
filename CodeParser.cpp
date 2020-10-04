#include "CodeParser.h"

#include <regex>

#include "CodeFile.h"
#include "StringHelper.h"

constexpr const char* FIND_MEMBER_FUNCTION_HEADERS_REGEX_STR =
R"(^[ \t]*((?:signed|unsigned[\s+])?[\w\d\_\t :<>,*&\n]+)\s+([\w\d\_:]+)::([\w\d\_]+)\(\s*([\w\d\_\t :<>,*&\/='";\n]*)\s*\)\s*((?:const)?)[ \t]*$)";

constexpr const char* FIND_MEMBER_FUNCTION_HEADER_DETAILS_REGEX_STR =
R"((?:^[ \t]*\/\/\s*\^\^x\n[ \t]*\/\/.*\n[ \t]*\/\/\s*3([a-zA-Z_]{3})\s+([a-zA-Z0-9\_\-\.\(\) \t]+)\n(?:[\/\/a-zA-Z0-9\_\-\.\(\) \t\n]+)?)?^[ \t]*((?:signed|unsigned[\s+])?[\w\d\_\t :<>,*&\n]+)\s+([\w\d\_:]+)::([\w\d\_]+)\(\s*([\w\d\_\t :<>,*&\/='";\n]*)\s*\)\s*((?:const)?)[ \t]*$)";

constexpr const char* FIND_SINGLELINE_COMMENTS_REGEX_STR =
R"((?:\/\/.*))";

constexpr const char* FIND_MULTILINE_COMMENTS_REGEX_STR =
R"((?:\/\*.*?\*\/))";

// ^^x
// std::vector<SFindMemberFunctionHeaderResult> CCodeParser::FindMemberFunctionHeaders
// 3BGO JIRA-238 02-10-2020
std::vector<SFindMemberFunctionHeaderResult> CCodeParser::FindMemberFunctionHeaders( const CCodeFile& oCodeFile ) const
{
	const std::regex oRegexPattern{FIND_MEMBER_FUNCTION_HEADERS_REGEX_STR};
	const std::string& oCodeString = oCodeFile.GetContent();

	std::vector<SFindMemberFunctionHeaderResult> oResultVector{};

	const std::sregex_token_iterator oRegexEndIt{};
	for ( std::sregex_token_iterator oRegexBeginIt{ oCodeString.cbegin(), oCodeString.cend(), oRegexPattern }; oRegexBeginIt != oRegexEndIt; ++oRegexBeginIt )
	{
		SFindMemberFunctionHeaderResult oResult{};

		oResult.oHeaderString = *oRegexBeginIt;

		oResultVector.push_back( oResult );
	}

	return oResultVector;
}

// ^^x
// std::vector<SFindMemberFunctionHeaderDetailResult> CCodeParser::FindMemberFunctionHeadersDetails
// 3BGO JIRA-238 02-10-2020
std::vector<SFindMemberFunctionHeaderDetailResult> CCodeParser::FindMemberFunctionHeadersDetails( const CCodeFile& oCodeFile ) const
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
	const std::string& oCodeString = oCodeFile.GetContent();

	const std::sregex_token_iterator oRegexEndIt{};
	for ( std::sregex_token_iterator oRegexBeginIt{oCodeString.cbegin(), oCodeString.cend(), oRegexPattern, aiMatchGroups }; oRegexBeginIt != oRegexEndIt; ++oRegexBeginIt )
	{
		SFindMemberFunctionHeaderDetailResult oResult{};

		oResult.oHeaderResult.oHeaderString = *oRegexBeginIt++;

		oResult.oHeaderDataset.oAuthorString = CStringHelper::Replace( CStringHelper::SimplifyString( *oRegexBeginIt++ ), '\n', ' ' );
		oResult.oHeaderDataset.oInformationString = CStringHelper::Replace( CStringHelper::SimplifyString( *oRegexBeginIt++ ), '\n', ' ' );
		oResult.oHeaderDataset.oReturnTypeString = CStringHelper::Replace( CStringHelper::SimplifyString( *oRegexBeginIt++ ), '\n', ' ' );
		oResult.oHeaderDataset.oClassNameString = CStringHelper::Replace( CStringHelper::SimplifyString( *oRegexBeginIt++ ), '\n', ' ' );
		oResult.oHeaderDataset.oNameString = CStringHelper::Replace( CStringHelper::SimplifyString( *oRegexBeginIt++ ), '\n', ' ' );
		oResult.oHeaderDataset.oArgumentsString = CStringHelper::Replace( CStringHelper::SimplifyString( *oRegexBeginIt++ ), '\n', ' ' );
		oResult.oHeaderDataset.oModifierString = CStringHelper::Replace( CStringHelper::SimplifyString( *oRegexBeginIt++ ), '\n', ' ' );

		oResultVector.push_back( oResult );
	}

	return oResultVector;
}

// ^^x
// std::vector<SFindMemberFunctionResult> CCodeParser::FindMemberFunctions
// 3BGO JIRA-238 02-10-2020
std::vector<SFindMemberFunctionResult> CCodeParser::FindMemberFunctions( const CCodeFile& oCodeFile ) const
{
	std::vector<SFindMemberFunctionResult> oResultVector{};

	const std::string oCodeString = oCodeFile.GetContent();
	const std::vector<SFindMemberFunctionHeaderResult> oFindFunctionHeaderResultVector = FindMemberFunctionHeaders( oCodeFile );
	const std::string oCodeNonSinglelineString = RemoveSinglelineComments( oCodeString );

	std::size_t uiFindCurrentOffsetPos = 0u;

	for ( const SFindMemberFunctionHeaderResult& oFunctionHeaderResult : oFindFunctionHeaderResultVector )
	{
		SFindMemberFunctionResult oResult{};
		oResult.oHeaderResult = oFunctionHeaderResult;

		const std::size_t uiFunctionBracketOpenPos = FindFunctionBracketOpenPosition( oCodeNonSinglelineString, oFunctionHeaderResult.oHeaderString, uiFindCurrentOffsetPos );

		if ( uiFunctionBracketOpenPos != std::string::npos )
		{
			uiFindCurrentOffsetPos = uiFunctionBracketOpenPos + 1u;
			uiFindCurrentOffsetPos = FindFunctionBracketClosePosition( oCodeNonSinglelineString, uiFindCurrentOffsetPos );

			if ( uiFindCurrentOffsetPos != std::string::npos )
			{
				const std::size_t uiFunctionBracketClosePos = uiFindCurrentOffsetPos - uiFunctionBracketOpenPos;

				oResult.oBodyDataset.oBodyString = oCodeNonSinglelineString.substr( uiFunctionBracketOpenPos, uiFunctionBracketClosePos );

				oResultVector.push_back( oResult );
			}
		}
	}

	return oResultVector;
}

// ^^x
// std::vector<SFindMemberFunctionDetailResult> CCodeParser::FindMemberFunctionsDetails
// 3BGO JIRA-238 02-10-2020
std::vector<SFindMemberFunctionDetailResult> CCodeParser::FindMemberFunctionsDetails( const CCodeFile& oCodeFile ) const
{
	std::vector<SFindMemberFunctionDetailResult> oResultVector{};

	const std::string oCodeString = oCodeFile.GetContent();
	const std::vector<SFindMemberFunctionHeaderDetailResult> oFindFunctionHeaderDetailResultVector = FindMemberFunctionHeadersDetails( oCodeFile );
	const std::string oCodeNonSinglelineString = RemoveSinglelineComments( oCodeString );

	std::size_t uiFindCurrentOffsetPos = 0u;

	for ( const SFindMemberFunctionHeaderDetailResult& oFunctionHeaderDetailResult : oFindFunctionHeaderDetailResultVector )
	{
		SFindMemberFunctionDetailResult oResult{};
		oResult.oHeaderResult = oFunctionHeaderDetailResult.oHeaderResult;
		oResult.oHeaderDataset = oFunctionHeaderDetailResult.oHeaderDataset;

		const std::size_t uiFunctionBracketOpenPos = FindFunctionBracketOpenPosition( oCodeNonSinglelineString, oFunctionHeaderDetailResult.oHeaderResult.oHeaderString, uiFindCurrentOffsetPos );

		if ( uiFunctionBracketOpenPos != std::string::npos )
		{
			uiFindCurrentOffsetPos = uiFunctionBracketOpenPos + 1u;
			uiFindCurrentOffsetPos = FindFunctionBracketClosePosition( RemoveMultilineComments( oCodeNonSinglelineString ), uiFindCurrentOffsetPos );

			if ( uiFindCurrentOffsetPos != std::string::npos )
			{
				const std::size_t uiFunctionBracketClosePos = uiFindCurrentOffsetPos - uiFunctionBracketOpenPos;

				oResult.oBodyDataset.oBodyString = oCodeNonSinglelineString.substr( uiFunctionBracketOpenPos, uiFunctionBracketClosePos );

				oResultVector.push_back( oResult );
			}
		}
	}

	return oResultVector;
}

// ^^x
// std::string CCodeParser::RemoveSinglelineComments
// 3BGO JIRA-238 02-10-2020
std::string CCodeParser::RemoveSinglelineComments( const std::string& oCodeString ) const
{
	return std::regex_replace( oCodeString, std::regex{ FIND_SINGLELINE_COMMENTS_REGEX_STR }, "" );
}

// ^^x
// std::string CCodeParser::RemoveMultilineComments
// 3BGO JIRA-238 02-10-2020
std::string CCodeParser::RemoveMultilineComments( const std::string& oCodeString ) const
{
	return std::regex_replace( oCodeString, std::regex{ FIND_MULTILINE_COMMENTS_REGEX_STR }, "" );
}

// ^^x
// std::size_t CCodeParser::FindFunctionBracketOpenPosition
// 3BGO JIRA-238 02-10-2020
std::size_t CCodeParser::FindFunctionBracketOpenPosition( const std::string& oCodeString, const std::string& oFunctionHeaderString, std::size_t uiCurrentOffsetPos ) const
{
	const std::size_t uiFunctionHeaderBegPos = oCodeString.find( oFunctionHeaderString, uiCurrentOffsetPos );
	const std::size_t uiFunctionHeaderEndPos = uiFunctionHeaderBegPos + oFunctionHeaderString.size();

	return oCodeString.find_first_of( '{', uiFunctionHeaderEndPos );
}

// ^^x
// std::size_t CCodeParser::FindFunctionBracketClosePosition
// 3BGO JIRA-238 02-10-2020
std::size_t CCodeParser::FindFunctionBracketClosePosition( const std::string& oCodeString, std::size_t uiCurrentOffsetPos ) const
{
	std::size_t uiFunctionBracketLevel{ 1u };

	bool bBeginCharacterLiteral{ false };
	bool bBeginStringLiteral{ false };

	while ( uiFunctionBracketLevel > 0u )
	{
		std::size_t uiSyntaxCharacterPos = oCodeString.find_first_of( "{}'\"", uiCurrentOffsetPos );

		if ( uiSyntaxCharacterPos != std::string::npos )
		{
			if ( oCodeString[uiSyntaxCharacterPos] == '{' )
			{
				if ( !bBeginCharacterLiteral && !bBeginStringLiteral )
				{
					++uiFunctionBracketLevel;
				}
			}
			else if ( oCodeString[uiSyntaxCharacterPos] == '}' )
			{
				if ( !bBeginCharacterLiteral && !bBeginStringLiteral )
				{
					--uiFunctionBracketLevel;
				}
			}
			else if ( oCodeString[uiSyntaxCharacterPos] == '\'' )
			{
				if ( !bBeginStringLiteral )
				{
					bBeginCharacterLiteral = !bBeginCharacterLiteral;
				}
			}
			else if ( oCodeString[uiSyntaxCharacterPos] == '"' )
			{
				bBeginStringLiteral = !bBeginStringLiteral;
			}
			else if ( oCodeString[uiSyntaxCharacterPos] == '\\' )
			{
				if ( !bBeginStringLiteral )
				{
					uiSyntaxCharacterPos = oCodeString.find_first_not_of( " \t\n", uiSyntaxCharacterPos + 1u );
				}
			}
			
			uiCurrentOffsetPos = uiSyntaxCharacterPos + 1u;
		}
		else
		{
			break;
		}
	}

	if ( uiFunctionBracketLevel > 0u )
	{
		uiCurrentOffsetPos = std::string::npos;
	}

	return uiCurrentOffsetPos;
}
