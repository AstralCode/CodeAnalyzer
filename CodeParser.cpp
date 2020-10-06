#include "CodeParser.h"

#include <regex>

#include "CodeFile.h"
#include "StringHelper.h"

const std::string FIND_MEMBER_FUNCTION_HEADER_AUTHOR_REGEX_STR =
R"([a-zA-Z_]{2,3})";

const std::string FIND_MEMBER_FUNCTION_HEADER_INFO_REGEX_STR =
R"(^[ \t]*\/\/\s*\^\^x\n[ \t]*\/\/.*\n[ \t]*\/\/\s*3(<developer>)\s+([a-zA-Z0-9\_\-\. \t]+)\n(?:[\/\/a-zA-Z0-9\_\-\.\(\) \t\n]+)?)";

const std::string FIND_MEMBER_FUNCTION_HEADER_REGEX_STR =
R"(^[ \t]*((?:signed|unsigned[\s+])?[\w\d\_\t :<>,*&\n]+)\s+([\w\d\_:]+)::([\w\d\_]+)\(\s*([\w\d\_\t \-:<>,*&\/='";\n]+)?\s*\)\s*(const)?[ \t]*$)";

constexpr const char* FIND_SINGLELINE_COMMENTS_REGEX_STR =
R"((?:\/\/.*))";

constexpr const char* FIND_MULTILINE_COMMENTS_REGEX_STR =
R"((?:\/\*.*?\*\/))";

// ^^x
// std::vector<SMemberFunctionHeaderDataset> CCodeParser::FindMemberFunctionHeaders
// 3BGO JIRA-238 02-10-2020
std::vector<SMemberFunctionHeaderDataset> CCodeParser::FindMemberFunctionHeaders( const std::string oCodeString, std::optional<std::string> oDeveloperString ) const
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

	std::regex oRegexPattern{ PrepareFindMemberFunctionRegexString( oDeveloperString ), std::regex_constants::icase };

	const std::sregex_token_iterator oRegexEndIt{};
	for ( std::sregex_token_iterator oRegexBeginIt{ oCodeString.cbegin(), oCodeString.cend(), oRegexPattern, aiMatchGroups }; oRegexBeginIt != oRegexEndIt; ++oRegexBeginIt )
	{
		SMemberFunctionHeaderDataset oDataset{};

		oDataset.oHeaderString = *oRegexBeginIt++;

		if ( oRegexBeginIt->matched )
		{
			oDataset.oAuthorString = SimplifyCode( *oRegexBeginIt );
		}

		++oRegexBeginIt;

		if ( oRegexBeginIt->matched )
		{
			oDataset.oInformationString = SimplifyCode( *oRegexBeginIt );
		}

		++oRegexBeginIt;

		oDataset.oReturnTypeString = SimplifyCode( *oRegexBeginIt++ );
		oDataset.oClassNameString = SimplifyCode( *oRegexBeginIt++ );
		oDataset.oNameString = SimplifyCode( *oRegexBeginIt++ );
		
		if ( oRegexBeginIt->matched )
		{
			oDataset.oArgumentsString = SimplifyCode( *oRegexBeginIt );
		}

		++oRegexBeginIt;
		
		if ( oRegexBeginIt->matched )
		{
			oDataset.oModifierString = SimplifyCode( *oRegexBeginIt );
		}
		
		oDatasetVector.push_back( oDataset );
	}

	return oDatasetVector;
}

// ^^x
// std::vector<SMemberFunctionHeaderDataset> CCodeParser::FindMemberFunctions
// 3BGO JIRA-238 02-10-2020
std::vector<SMemberFunctionHeaderDataset> CCodeParser::FindMemberFunctions( const std::string oCodeString, std::optional<std::string> oDeveloperString ) const
{
	std::vector<SMemberFunctionHeaderDataset> oFunctionHeaderDatasetVector = FindMemberFunctionHeaders( oCodeString, oDeveloperString );
	
	const std::string oCodeWithoutCommentsString = RemoveSingleLineComments( oCodeString );

	std::size_t uiCurrentSearchOffsetPos{ 0u };

	for ( SMemberFunctionHeaderDataset& oFunctionHeaderResult : oFunctionHeaderDatasetVector )
	{
		const std::string oMemberFunctionString = oFunctionHeaderResult.oClassNameString + "::" + oFunctionHeaderResult.oNameString;
		const std::size_t uiFunctionBracketOpenPos = FindFunctionBracketOpenPosition( oCodeWithoutCommentsString, oMemberFunctionString, uiCurrentSearchOffsetPos );
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
// std::string CCodeParser::PrepareFindMemberFunctionHeaderRegexString
// 3BGO JIRA-238 06-10-2020
std::string CCodeParser::PrepareFindMemberFunctionHeaderRegexString( std::optional<std::string> oDeveloperString ) const
{
	std::string oRegexPatternString{ FIND_MEMBER_FUNCTION_HEADER_INFO_REGEX_STR };

	if ( oDeveloperString.has_value() )
	{
		oRegexPatternString = CStringHelper::Replace( oRegexPatternString, "<developer>", *oDeveloperString );
	}
	else
	{
		oRegexPatternString = CreateGroupRegexString( CStringHelper::Replace( oRegexPatternString, "<developer>", FIND_MEMBER_FUNCTION_HEADER_AUTHOR_REGEX_STR ), false, true );
	}

	return oRegexPatternString;
}

// ^^x
// std::string CCodeParser::PrepareFindMemberFunctionRegexString
// 3BGO JIRA-238 06-10-2020
std::string CCodeParser::PrepareFindMemberFunctionRegexString( std::optional<std::string> oDeveloperString ) const
{
	std::string oRegexPatternString{ PrepareFindMemberFunctionHeaderRegexString( oDeveloperString ) };

	oRegexPatternString += FIND_MEMBER_FUNCTION_HEADER_REGEX_STR;

	return oRegexPatternString;
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

// ^^x
// std::string CCodeParser::SimplifyCode
// 3BGO JIRA-238 05-10-2020
std::string CCodeParser::SimplifyCode( const std::string& oCodeString ) const
{
	return CStringHelper::Replace( CStringHelper::SimplifyString( oCodeString ), '\n', ' ' );
}

// ^^x
// std::string CCodeParser::CreateGroupRegexString
// 3BGO JIRA-238 05-10-2020
std::string CCodeParser::CreateGroupRegexString( const std::string& oRegexString, bool bCapturingGroup, bool bOptionalGroup ) const
{
	std::string oResultString{ "(" + oRegexString + ")" };
	
	if ( !bCapturingGroup )
	{
		oResultString.insert( 1u, "?:" );
	}

	if ( bOptionalGroup )
	{
		oResultString.insert( oResultString.size(), "?" );
	}

	return oResultString;
}
