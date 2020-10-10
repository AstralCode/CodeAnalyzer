#include "CodeParser.h"

#include <regex>

#include "CodeFile.h"
#include "StringHelper.h"

enum EFindMemberFunctionRegexMatchGroups
{
	eRegexMatch,
	eFunctionAuthorGroup,
	eFunctionProjectGroup,
	eFunctionReturnTypeGroup,
	eFunctionClassNameGroup,
	eFunctionDestructorGroup,
	eFunctionNameGroup,
	eFunctionArgumentListGroup
};

constexpr const char* FIND_MEMBER_FUNCTION_HEADER_INFORMATION_REGEX_STR =
R"((?:^[ \t]*\/\/\s*\^\^x\n[ \t]*\/\/.*\n[ \t]*\/\/\s*3([a-zA-Z_]{2,3})\s+([a-zA-Z0-9\_\-\. \t]+)\n(?:[\/\/a-zA-Z0-9\_\-\.\(\) \t\n]+)?)?)";

constexpr const char* FIND_MEMBER_FUNCTION_HEADER_REGEX_STR =
R"(^[ \t]*(?:([\w\d\t :<>,*&\n]+)\s+)?([\w\d\_:]+)::(\~)?([\w\d\_]+)\(\s*([\w\d\_\t \-:<>,*&\/='";\n]+)?\s*\)\s*(?:\:)?(?:const)?[ \t]*$)";

constexpr const char* FIND_SINGLELINE_COMMENTS_REGEX_STR =
R"((?:\/\/.*))";

constexpr const char* FIND_MULTILINE_COMMENTS_REGEX_STR =
R"((?:\/\*.*?\*\/))";

// ^^x
// unsigned int CCodeParser::CountLines
// 3BGO JIRA-238 02-10-2020
unsigned int CCodeParser::CountLines( std::string_view oCodeString ) const
{
	return CStringHelper::SplitLines( oCodeString ).size();
}

// ^^x
// std::vector<SFindDataResult<CFunction>> CCodeParser::FindMemberFunctionHeaders
// 3BGO JIRA-238 02-10-2020
std::vector<SFindDataResult<CFunction>> CCodeParser::FindMemberFunctionHeaders( std::string_view oCodeString ) const
{
	std::vector<SFindDataResult<CFunction>> oMemberFunctionVector{};
	std::regex oRegexPattern{ PrepareFindMemberFunctionRegexString(), std::regex_constants::icase };

	const std::regex_iterator<std::string_view::const_iterator> oRegexEndIt{};
	for ( std::regex_iterator<std::string_view::const_iterator> oRegexBeginIt{ oCodeString.cbegin(), oCodeString.cend(), oRegexPattern }; oRegexBeginIt != oRegexEndIt; ++oRegexBeginIt )
	{
		std::match_results<std::string_view::const_iterator> oRegexMatchGroups = *oRegexBeginIt;

		if ( oRegexMatchGroups[eFunctionClassNameGroup].matched )
		{
			CFunction oMemberFunction{};
			oMemberFunction.SetName( oRegexMatchGroups[eFunctionNameGroup].str() );
			oMemberFunction.SetClassName( SimplifyCode( oRegexMatchGroups[eFunctionClassNameGroup].str() ) );

			if ( oRegexMatchGroups[eFunctionReturnTypeGroup].matched )
			{
				oMemberFunction.SetReturnType( oRegexMatchGroups[eFunctionReturnTypeGroup].str() );
			}

			if ( oRegexMatchGroups[eFunctionDestructorGroup].matched )
			{
				oMemberFunction.SetDestructor( oRegexMatchGroups[eFunctionDestructorGroup].str() );
			}

			if ( oRegexMatchGroups[eFunctionArgumentListGroup].matched )
			{
				oMemberFunction.SetArgumentList( SimplifyCode( oRegexMatchGroups[eFunctionArgumentListGroup].str() ) );
			}

			if ( oRegexMatchGroups[eFunctionAuthorGroup].matched && oRegexMatchGroups[eFunctionProjectGroup].matched )
			{
				SFunctionInformation oFunctionInformation{};
				oFunctionInformation.m_oAuthorString = SimplifyCode( oRegexMatchGroups[eFunctionAuthorGroup].str() );
				oFunctionInformation.m_oProjectString = SimplifyCode( oRegexMatchGroups[eFunctionProjectGroup].str() );

				oMemberFunction.SetInformation( oFunctionInformation );
			}

			oMemberFunctionVector.push_back( { oRegexMatchGroups[eRegexMatch], oMemberFunction } );
		}
	}

	return oMemberFunctionVector;
}

// ^^x
// std::vector<SFindDataResult<CFunction>> CCodeParser::FindMemberFunctions
// 3BGO JIRA-238 02-10-2020
std::vector<SFindDataResult<CFunction>> CCodeParser::FindMemberFunctions( std::string_view oCodeString ) const
{
	std::vector<SFindDataResult<CFunction>> oMemberFunctionVector = FindMemberFunctionHeaders( oCodeString );
	
	std::size_t uiCurrentSearchOffsetPos{ 0u };

	for ( SFindDataResult<CFunction>& oMemberFunction : oMemberFunctionVector )
	{
		const std::string oCodeWithoutCommentsString = RemoveSingleLineComments( oCodeString );
		const std::size_t uiFunctionBracketOpenPos = FindFunctionBracketOpenPosition( oCodeWithoutCommentsString, oMemberFunction.oData.GetName(), uiCurrentSearchOffsetPos );
		if ( uiFunctionBracketOpenPos != std::string::npos )
		{
			uiCurrentSearchOffsetPos = uiFunctionBracketOpenPos + 1u;

			const std::size_t uiFunctionBracketClosePos = FindFunctionBracketClosePosition( oCodeWithoutCommentsString, uiCurrentSearchOffsetPos );
			if ( uiFunctionBracketClosePos != std::string::npos )
			{
				uiCurrentSearchOffsetPos = uiFunctionBracketClosePos;

				oMemberFunction.oData.SetBody( RetrieveBodyFunction( oCodeWithoutCommentsString, uiFunctionBracketOpenPos, uiFunctionBracketClosePos ) );

				++uiCurrentSearchOffsetPos;
			}
		}
	}

	return oMemberFunctionVector;
}

// ^^x
// std::string CCodeParser::RemoveSingleLineComments
// 3BGO JIRA-238 02-10-2020
std::string CCodeParser::RemoveSingleLineComments( std::string_view oCodeString ) const
{
	return std::regex_replace( oCodeString.data(), std::regex{ FIND_SINGLELINE_COMMENTS_REGEX_STR }, "" );
}

// ^^x
// std::string CCodeParser::RemoveMultilineComments
// 3BGO JIRA-238 02-10-2020
std::string CCodeParser::RemoveMultilineComments( std::string_view oCodeString ) const
{
	return std::regex_replace( oCodeString.data(), std::regex{ FIND_MULTILINE_COMMENTS_REGEX_STR }, "" );
}

// ^^x
// std::string CCodeParser::PrepareFindMemberFunctionRegexString
// 3BGO JIRA-238 06-10-2020
std::string CCodeParser::PrepareFindMemberFunctionRegexString() const
{
	std::string oRegexPatternString{ FIND_MEMBER_FUNCTION_HEADER_INFORMATION_REGEX_STR };
	oRegexPatternString += FIND_MEMBER_FUNCTION_HEADER_REGEX_STR;

	return oRegexPatternString;
}

// ^^x
// std::size_t CCodeParser::FindFunctionBracketOpenPosition
// 3BGO JIRA-238 02-10-2020
std::size_t CCodeParser::FindFunctionBracketOpenPosition( std::string_view oCodeString, std::string_view oFunctionHeaderString, const std::size_t uiCurrentSearchOffsetPos ) const
{
	const std::size_t uiFunctionHeaderBegPos = oCodeString.find( oFunctionHeaderString, uiCurrentSearchOffsetPos );
	const std::size_t uiFunctionHeaderEndPos = uiFunctionHeaderBegPos + oFunctionHeaderString.size();

	return oCodeString.find_first_of( '{', uiFunctionHeaderEndPos );
}

// ^^x
// std::size_t CCodeParser::FindFunctionBracketClosePosition
// 3BGO JIRA-238 02-10-2020
std::size_t CCodeParser::FindFunctionBracketClosePosition( std::string_view oCodeString, std::size_t uiCurrentSearchOffsetPos ) const
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
// std::string_view CCodeParser::RetrieveBodyFunction
// 3BGO JIRA-238 02-10-2020
std::string_view CCodeParser::RetrieveBodyFunction( std::string_view oCodeString, const std::size_t uiFunctionBracketOpenPos, const std::size_t uiFunctionBracketClosePos ) const
{
	const std::size_t uiFunctionBodyLength = uiFunctionBracketClosePos - uiFunctionBracketOpenPos;

	return oCodeString.substr( uiFunctionBracketOpenPos, uiFunctionBodyLength );
}

// ^^x
// std::string CCodeParser::SimplifyCode
// 3BGO JIRA-238 05-10-2020
std::string CCodeParser::SimplifyCode( std::string_view oCodeString ) const
{
	return CStringHelper::Replace( CStringHelper::SimplifyString( oCodeString ), '\n', ' ' );
}
