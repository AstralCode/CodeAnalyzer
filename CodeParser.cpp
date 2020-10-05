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
// std::vector<SMemberFunctionHeaderDataset> CCodeParser::FindMemberFunctionHeaders
// 3BGO JIRA-238 02-10-2020
std::vector<SMemberFunctionHeaderDataset> CCodeParser::FindMemberFunctionHeaders( const std::string oCodeString ) const
{
	const std::regex oRegexPattern{ FIND_MEMBER_FUNCTION_HEADERS_REGEX_STR };

	std::vector<SMemberFunctionHeaderDataset> oDatasetVector{};

	const std::sregex_token_iterator oRegexEndIt{};
	for ( std::sregex_token_iterator oRegexBeginIt{ oCodeString.cbegin(), oCodeString.cend(), oRegexPattern }; oRegexBeginIt != oRegexEndIt; ++oRegexBeginIt )
	{
		SMemberFunctionHeaderDataset oDataset{};

		oDataset.oHeaderString = *oRegexBeginIt;

		oDatasetVector.push_back( oDataset );
	}

	return oDatasetVector;
}

// ^^x
// std::vector<SMemberFunctionHeaderDataset> CCodeParser::FindMemberFunctionHeadersDetails
// 3BGO JIRA-238 02-10-2020
std::vector<SMemberFunctionHeaderDataset> CCodeParser::FindMemberFunctionHeadersDetails( const std::string oCodeString ) const
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

	std::vector<SMemberFunctionHeaderDataset> oDatasetVector{};

	const int aiMatchGroups[] = { eEntireMatch, eAuthor, eInfo, eReturnType, eClassName, eName, eArgList, eModifier };

	const std::regex oRegexPattern{ FIND_MEMBER_FUNCTION_HEADER_DETAILS_REGEX_STR };

	const std::sregex_token_iterator oRegexEndIt{};
	for ( std::sregex_token_iterator oRegexBeginIt{ oCodeString.cbegin(), oCodeString.cend(), oRegexPattern, aiMatchGroups }; oRegexBeginIt != oRegexEndIt; ++oRegexBeginIt )
	{
		SMemberFunctionHeaderDataset oDataset{};

		oDataset.oHeaderString = *oRegexBeginIt++;
		oDataset.oAuthorString = CStringHelper::Replace( CStringHelper::SimplifyString( *oRegexBeginIt++ ), '\n', ' ' );
		oDataset.oInformationString = CStringHelper::Replace( CStringHelper::SimplifyString( *oRegexBeginIt++ ), '\n', ' ' );
		oDataset.oReturnTypeString = CStringHelper::Replace( CStringHelper::SimplifyString( *oRegexBeginIt++ ), '\n', ' ' );
		oDataset.oClassNameString = CStringHelper::Replace( CStringHelper::SimplifyString( *oRegexBeginIt++ ), '\n', ' ' );
		oDataset.oNameString = CStringHelper::Replace( CStringHelper::SimplifyString( *oRegexBeginIt++ ), '\n', ' ' );
		oDataset.oArgumentsString = CStringHelper::Replace( CStringHelper::SimplifyString( *oRegexBeginIt++ ), '\n', ' ' );
		oDataset.oModifierString = CStringHelper::Replace( CStringHelper::SimplifyString( *oRegexBeginIt ), '\n', ' ' );

		oDatasetVector.push_back( oDataset );
	}

	return oDatasetVector;
}

// ^^x
// std::vector<SMemberFunctionHeaderDataset> CCodeParser::FindMemberFunctions
// 3BGO JIRA-238 02-10-2020
std::vector<SMemberFunctionHeaderDataset> CCodeParser::FindMemberFunctions( const std::string oCodeString, const bool bFindHeaderDetails/* = false*/ ) const
{
	std::vector<SMemberFunctionHeaderDataset> oFunctionHeaderDatasetVector = ( bFindHeaderDetails ? FindMemberFunctionHeadersDetails( oCodeString ) : FindMemberFunctionHeaders( oCodeString ) );
	
	const std::string oCodeWithoutCommentsString = RemoveSingleLineComments( oCodeString );

	std::size_t uiCurrentSearchOffsetPos{ 0u };

	for ( SMemberFunctionHeaderDataset& oFunctionHeaderResult : oFunctionHeaderDatasetVector )
	{
		const std::size_t uiFunctionBracketOpenPos = FindFunctionBracketOpenPosition( oCodeWithoutCommentsString, oFunctionHeaderResult.oHeaderString, uiCurrentSearchOffsetPos );
		if ( uiFunctionBracketOpenPos != std::string::npos )
		{
			uiCurrentSearchOffsetPos = uiFunctionBracketOpenPos + 1u;

			const std::size_t uiFunctionBracketClosePos = FindFunctionBracketClosePosition( oCodeWithoutCommentsString, uiCurrentSearchOffsetPos );
			if ( uiFunctionBracketClosePos != std::string::npos )
			{
				uiCurrentSearchOffsetPos = uiFunctionBracketClosePos;

				oFunctionHeaderResult.oBodyString = RetrieveBodyFunction( oCodeWithoutCommentsString, uiFunctionBracketOpenPos, uiFunctionBracketClosePos );
			}
		}
	}

	return oFunctionHeaderDatasetVector;
}

// ^^x
// std::string CCodeParser::RemoveSingleLineComments
// 3BGO JIRA-238 02-10-2020
std::string CCodeParser::RemoveSingleLineComments( const std::string& oCodeString ) const
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
std::size_t CCodeParser::FindFunctionBracketOpenPosition( const std::string& oCodeString, const std::string& oFunctionHeaderString, const std::size_t uiCurrentSearchOffsetPos ) const
{
	const std::size_t uiFunctionHeaderBegPos = oCodeString.find( oFunctionHeaderString, uiCurrentSearchOffsetPos );
	const std::size_t uiFunctionHeaderEndPos = uiFunctionHeaderBegPos + oFunctionHeaderString.size();

	return oCodeString.find_first_of( '{', uiFunctionHeaderEndPos );
}

// ^^x
// std::size_t CCodeParser::FindFunctionBracketClosePosition
// 3BGO JIRA-238 02-10-2020
std::size_t CCodeParser::FindFunctionBracketClosePosition( const std::string& oCodeString, std::size_t uiCurrentSearchOffsetPos ) const
{
	std::size_t uiFunctionBracketLevel{ 1u };
	std::size_t uiSyntaxCharacterPos{ std::string::npos };

	bool bBeginCharacterLiteral{ false };
	bool bBeginStringLiteral{ false };

	while ( uiFunctionBracketLevel > 0u )
	{
		uiSyntaxCharacterPos = oCodeString.find_first_of( "{}'\"", uiCurrentSearchOffsetPos );

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
			
			uiCurrentSearchOffsetPos = uiSyntaxCharacterPos + 1u;
		}
		else
		{
			break;
		}
	}

	if ( uiFunctionBracketLevel > 0u )
	{
		uiCurrentSearchOffsetPos = std::string::npos;
	}

	return uiCurrentSearchOffsetPos;
}

// ^^x
// std::string CCodeParser::RetrieveBodyFunction
// 3BGO JIRA-238 02-10-2020
std::string CCodeParser::RetrieveBodyFunction( const std::string& oCodeString, const std::size_t uiFunctionBracketOpenPos, const std::size_t uiFunctionBracketClosePos ) const
{
	const std::size_t uiFunctionBodyLength = uiFunctionBracketClosePos - uiFunctionBracketOpenPos;

	return oCodeString.substr( uiFunctionBracketOpenPos, uiFunctionBodyLength );
}
