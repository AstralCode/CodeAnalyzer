#include "CodeParser.h"

#include <regex>

#include "CodeFile.h"
#include "StringHelper.h"

constexpr const char* FIND_FUNCTION_HEADER_INFORMATION_REGEX_STR =
R"((?:^[ \t]*\/\/\s*\^\^x\n[ \t]*\/\/.*\n[ \t]*\/\/\s*3([a-zA-Z_]{2,3})\s+([a-zA-Z0-9\_\-\. \t]+)\n(?:[\/\/a-zA-Z0-9\_\-\.\(\) \t\n]+)?)?)";

constexpr const char* FIND_GLOBAL_FUNCTION_HEADER_REGEX_STR =
R"(^[ \t]*(?:static\s+)?([\w:<>:,*&]{3,})(?:[\s\*\&]+)?(?:CALLBACK|__cdecl)?\s+([\w]{3,})\s*\(\s*([\w\t \.\-:<>,*&\/'";\n]+)?\s*\)[\t ]*$)";

constexpr const char* FIND_MEMBER_FUNCTION_HEADER_REGEX_STR =
R"(^[ \t]*(?:inline\s+)?(?:([\w:<>,*&]{3,})(?:[\s\*\&]+)?\s+)?(?:__cdecl\s+)?([\w:]+)::(\~)?([\w]+)\s*\(\s*([\w\t \.\-:<>,*&\/='";\n]+)?\s*\)\s*(?:const)?[ \t]*$)";

constexpr const char* FIND_SINGLELINE_COMMENTS_REGEX_STR =
R"((?:\/\/.*))";

constexpr const char* FIND_MULTILINE_COMMENTS_REGEX_STR =
R"((?:\/\*.*?\*\/))";

constexpr const char* FIND_DIRECTIVE_INCLUDE_REGEX_STR =
R"(^[\t ]*#include\s+(?:\"|\<)[\w\.]+(?:\"|\>)$)";

constexpr const char* FIND_MACRO_IMPLEMENT_DYNAMIC_REGEX_STR =
R"(^[\t ]*IMPLEMENT_DYNAMIC\s*\(.*\)$)";

constexpr const char* FIND_MACRO_IMPLEMENT_DYNCREATE_REGEX_STR =
R"(^[\t ]*IMPLEMENT_DYNCREATE\s*\(.*\)$)";

constexpr const char* FIND_MEMBER_DATA_LIST_INITIALIZATION =
R"(\:(?:\s+(?:\w+(?:[\{\(]).*(?:[\}\)])(?:\,)?)+)+)";

constexpr const char* FIND_VARIABLE_REGEX_STR =
R"(^[\t ]*((?:static\s+)?(?:const\s+)?(?:\w+::)*(?!(?:return|delete|class))(?:unsigned\s+|signed\s+)?\w{3,})(?:[*&]+)?\s+(\w+)(?:\[.*\)?\])?(?:\s*(?:=\s*.*?)|(?:\(.*\)|(?:\[.*\])))?;$)";

// ^^x
// unsigned int CCodeParser::CountLines
// 3BGO JIRA-238 02-10-2020
unsigned int CCodeParser::CountLines( const std::string& oCodeString ) const
{
	return CStringHelper::SplitLines( oCodeString ).size();
}

// ^^x
// std::vector<SFindDataResult<CFunction>> CCodeParser::FindGlobalFunctionHeaders
// 3BGO JIRA-238 02-10-2020
std::vector<SFindDataResult<CFunction>> CCodeParser::FindGlobalFunctionHeaders( const std::string& oCodeString ) const
{
	enum EGlobalFunctionRegexMatchGroups
	{
		eRegexMatch,
		eFunctionAuthorGroup,
		eFunctionProjectGroup,
		eFunctionReturnTypeGroup,
		eFunctionNameGroup,
		eFunctionArgumentListGroup
	};

	std::vector<SFindDataResult<CFunction>> oMemberFunctionVector{};
	std::regex oRegexPattern{ PrepareFindGlobalFunctionRegexString() };

	const std::sregex_iterator oRegexEndIt{};
	for ( std::sregex_iterator oRegexBeginIt{ oCodeString.cbegin(), oCodeString.cend(), oRegexPattern }; oRegexBeginIt != oRegexEndIt; ++oRegexBeginIt )
	{
		std::smatch oRegexMatchGroups = *oRegexBeginIt;

		CFunction oGlobalFunction{};
		oGlobalFunction.SetReturnType( oRegexMatchGroups[eFunctionReturnTypeGroup] );
		oGlobalFunction.SetName( oRegexMatchGroups[eFunctionNameGroup] );

		if ( oRegexMatchGroups[eFunctionArgumentListGroup].matched )
		{
			oGlobalFunction.SetArgumentList( SimplifyCode( oRegexMatchGroups[eFunctionArgumentListGroup] ) );
		}

		if ( oRegexMatchGroups[eFunctionAuthorGroup].matched && oRegexMatchGroups[eFunctionProjectGroup].matched )
		{
			CFunction::SInformation oFunctionInformation{};
			oFunctionInformation.oAuthorString = oRegexMatchGroups[eFunctionAuthorGroup];
			oFunctionInformation.oProjectString = oRegexMatchGroups[eFunctionProjectGroup];

			oGlobalFunction.SetInformation( oFunctionInformation );
		}

		oMemberFunctionVector.push_back( { oRegexMatchGroups[eRegexMatch], oRegexMatchGroups.position(), oGlobalFunction } );
	}

	return oMemberFunctionVector;
}

// ^^x
// std::vector<SFindDataResult<CFunction>> CCodeParser::FindGlobalFunctions
// 3BGO JIRA-238 02-10-2020
std::vector<SFindDataResult<CFunction>> CCodeParser::FindGlobalFunctions( const std::string& oCodeString ) const
{
	const std::string oCodeWithoutCommentsString = RemoveMemberFunctionBodies( oCodeString );

	std::vector<SFindDataResult<CFunction>> oGlobalFunctionVector = FindGlobalFunctionHeaders( oCodeWithoutCommentsString );
	RetrieveBodyFunctions( oCodeString, oGlobalFunctionVector );
	FindLocalVariables( oGlobalFunctionVector );

	return oGlobalFunctionVector;
}

// ^^x
// std::vector<SFindDataResult<CFunction>> CCodeParser::FindMemberFunctionHeaders
// 3BGO JIRA-238 02-10-2020
std::vector<SFindDataResult<CFunction>> CCodeParser::FindMemberFunctionHeaders( const std::string& oCodeString ) const
{
	enum EMemberFunctionRegexMatchGroups
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

	std::vector<SFindDataResult<CFunction>> oMemberFunctionVector{};
	std::regex oRegexPattern{ PrepareFindMemberFunctionRegexString(), std::regex_constants::icase };

	const std::sregex_iterator oRegexEndIt{};
	for ( std::sregex_iterator oRegexBeginIt{ oCodeString.cbegin(), oCodeString.cend(), oRegexPattern }; oRegexBeginIt != oRegexEndIt; ++oRegexBeginIt )
	{
		std::smatch oRegexMatchGroups = *oRegexBeginIt;

		CFunction oMemberFunction{};
		oMemberFunction.SetName( oRegexMatchGroups[eFunctionNameGroup] );
		oMemberFunction.SetClassName( SimplifyCode( oRegexMatchGroups[eFunctionClassNameGroup] ) );

		if ( oRegexMatchGroups[eFunctionReturnTypeGroup].matched )
		{
			oMemberFunction.SetReturnType( oRegexMatchGroups[eFunctionReturnTypeGroup] );
		}

		if ( oRegexMatchGroups[eFunctionDestructorGroup].matched )
		{
			oMemberFunction.SetDestructor( oRegexMatchGroups[eFunctionDestructorGroup] );
		}

		if ( oRegexMatchGroups[eFunctionArgumentListGroup].matched )
		{
			oMemberFunction.SetArgumentList( SimplifyCode( oRegexMatchGroups[eFunctionArgumentListGroup] ) );
		}

		if ( oRegexMatchGroups[eFunctionAuthorGroup].matched && oRegexMatchGroups[eFunctionProjectGroup].matched )
		{
			CFunction::SInformation oFunctionInformation{};
			oFunctionInformation.oAuthorString = oRegexMatchGroups[eFunctionAuthorGroup];
			oFunctionInformation.oProjectString = oRegexMatchGroups[eFunctionProjectGroup];

			oMemberFunction.SetInformation( oFunctionInformation );
		}

		oMemberFunctionVector.push_back( { oRegexMatchGroups[eRegexMatch], oRegexMatchGroups.position(), oMemberFunction } );
	}

	return oMemberFunctionVector;
}

// ^^x
// std::vector<SFindDataResult<CFunction>> CCodeParser::FindMemberFunctions
// 3BGO JIRA-238 02-10-2020
std::vector<SFindDataResult<CFunction>> CCodeParser::FindMemberFunctions( const std::string& oCodeString ) const
{
	std::vector<SFindDataResult<CFunction>> oMemberFunctionVector = FindMemberFunctionHeaders( oCodeString );
	RetrieveBodyFunctions( oCodeString, oMemberFunctionVector );
	FindLocalVariables( oMemberFunctionVector );

	return oMemberFunctionVector;
}

// ^^x
// std::vector<SFindDataResult<CVariable>> CSourceFile::FindGlobalVariables
// 3BGO JIRA-238 12-10-2020
std::vector<SFindDataResult<CVariable>> CCodeParser::FindGlobalVariables( const std::string& oCodeString ) const
{
	const std::vector<SFindDataResult<CFunction>> oGlobalFunctionHeaderVector = FindGlobalFunctionHeaders( oCodeString );
	const std::vector<SFindDataResult<CFunction>> oMemberFunctionHeaderVector = FindMemberFunctionHeaders( oCodeString );

	const std::string::size_type uiGlobalFunctionFirstPos = !oGlobalFunctionHeaderVector.empty() ? 
		oGlobalFunctionHeaderVector.front().iRegexMatchPos : std::string::npos;
	const std::string::size_type uiMemberFunctionFirstPos = !oMemberFunctionHeaderVector.empty() ?
		oMemberFunctionHeaderVector.front().iRegexMatchPos : std::string::npos;

	const std::string oTopCodeSectionString = oCodeString.substr( 0u, std::min( uiGlobalFunctionFirstPos, uiMemberFunctionFirstPos ) );

	return FindVariables( oTopCodeSectionString );
}

// ^^x
// std::vector<SFindDataResult<CVariable>> CSourceFile::FindLocalVariables
// 3BGO JIRA-238 12-10-2020
std::vector<SFindDataResult<CVariable>> CCodeParser::FindLocalVariables( const CFunction& oFunction ) const
{
	std::vector<SFindDataResult<CVariable>> oLocalVariableVector{};

	if ( oFunction.GetBody().has_value() )
	{
		oLocalVariableVector = FindVariables( *oFunction.GetBody() );
	}

	return oLocalVariableVector;
}

// ^^x
// std::vector<SFindDataResult<CVariable>> CSourceFile::FindVariables
// 3BGO JIRA-238 14-10-2020
std::vector<SFindDataResult<CVariable>> CCodeParser::FindVariables( const std::string& oCodeString ) const
{
	std::regex oRegexPattern{ FIND_VARIABLE_REGEX_STR };

	enum EVariableRegexMatchGroups
	{
		eRegexMatch,
		eVariableTypeGroup,
		eVariableNameGroup,
	};

	std::vector<SFindDataResult<CVariable>> oVariableVector{};

	const std::sregex_iterator oRegexEndIt{};
	for ( std::sregex_iterator oRegexBeginIt{ oCodeString.cbegin(), oCodeString.cend(), oRegexPattern }; oRegexBeginIt != oRegexEndIt; ++oRegexBeginIt )
	{
		std::smatch oRegexMatchGroups = *oRegexBeginIt;

		CVariable oVariable{};
		oVariable.SetType( oRegexMatchGroups[eVariableTypeGroup] );
		oVariable.SetName( oRegexMatchGroups[eVariableNameGroup] );

		oVariableVector.push_back( { oRegexMatchGroups[eRegexMatch], oRegexMatchGroups.position(), oVariable } );
	}

	return oVariableVector;
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
// std::string CCodeParser::RemoveIncludeDirectives
// 3BGO JIRA-238 02-10-2020
std::string CCodeParser::RemoveIncludeDirectives( const std::string& oCodeString ) const
{
	return std::regex_replace( oCodeString, std::regex{ FIND_DIRECTIVE_INCLUDE_REGEX_STR }, "" );
}

// ^^x
// std::string CCodeParser::RemoveImplementDynamicMacro
// 3BGO JIRA-238 02-10-2020
std::string CCodeParser::RemoveImplementDynamicMacro( const std::string& oCodeString ) const
{
	return std::regex_replace( oCodeString, std::regex{ FIND_MACRO_IMPLEMENT_DYNAMIC_REGEX_STR }, "" );
}

// ^^x
// std::string CCodeParser::RemoveImplementDyncreateMacro
// 3BGO JIRA-238 02-10-2020
std::string CCodeParser::RemoveImplementDyncreateMacro( const std::string& oCodeString ) const
{
	return std::regex_replace( oCodeString, std::regex{ FIND_MACRO_IMPLEMENT_DYNCREATE_REGEX_STR }, "" );
}

// ^^x
// std::string CCodeParser::RemoveMessageMapMacro
// 3BGO JIRA-238 02-10-2020
std::string CCodeParser::RemoveMessageMapMacro( const std::string& oCodeString ) const
{
	std::string oResultString{ oCodeString };

	const std::string::size_type uiMessageMapBegPos = oResultString.find( "BEGIN_MESSAGE_MAP" );
	if ( uiMessageMapBegPos != std::string::npos )
	{
		const std::string::size_type uiMessageMapEndPos = oResultString.find( "END_MESSAGE_MAP()" );
		oResultString.erase( uiMessageMapBegPos, ( uiMessageMapEndPos - uiMessageMapBegPos ) + std::string{ "END_MESSAGE_MAP()" }.size() );
	}

	return oResultString;
}

// ^^x
// std::string CCodeParser::RemoveMemberDataListInitialization
// 3BGO JIRA-238 02-10-2020
std::string CCodeParser::RemoveMemberDataListInitialization( const std::string& oCodeString ) const
{
	return std::regex_replace( oCodeString, std::regex{ FIND_MEMBER_DATA_LIST_INITIALIZATION }, "\n" );
}

// ^^x
// std::string CCodeParser::RemoveMemberFunctionBodies
// 3BGO JIRA-238 02-10-2020
std::string CCodeParser::RemoveMemberFunctionBodies( const std::string& oCodeString ) const
{
	std::string oCodeWithoutCommentsString = RemoveSingleLineComments( oCodeString );
	std::string::size_type uiCurrentCodeOffsetPos{ 0u };

	const std::vector<SFindDataResult<CFunction>> oMemberFunctionVector = FindMemberFunctions( oCodeString );
	for ( const SFindDataResult<CFunction>& oMemberFunction : oMemberFunctionVector )
	{
		const std::string::size_type uiMemberFunctionBodyBegPos = oCodeWithoutCommentsString.find( *oMemberFunction.oData.GetBody(), uiCurrentCodeOffsetPos );
		if ( uiMemberFunctionBodyBegPos != std::string::npos )
		{
			oCodeWithoutCommentsString.erase( uiMemberFunctionBodyBegPos, oMemberFunction.oData.GetBody()->size() );
			uiCurrentCodeOffsetPos = uiMemberFunctionBodyBegPos;
		}
	}

	return oCodeWithoutCommentsString;
}

// ^^x
// void CCodeParser::RetrieveBodyFunctions
// 3BGO JIRA-238 05-10-2020
void CCodeParser::RetrieveBodyFunctions( const std::string& oCodeString, std::vector<SFindDataResult<CFunction>>& oMemberFunctionVector ) const
{
	std::string::size_type uiCurrentCodeOffsetPos{ 0u };

	for ( SFindDataResult<CFunction>& oMemberFunction : oMemberFunctionVector )
	{
		const std::string oMemberFunctionBody = RetrieveBodyFunction( oCodeString, oMemberFunction.oRegexMatchString, uiCurrentCodeOffsetPos );
		if ( !oMemberFunctionBody.empty() )
		{
			oMemberFunction.oData.SetBody( oMemberFunctionBody );
		}
	}
}

// ^^x
// void CCodeParser::FindLocalVariables
// 3BGO JIRA-238 12-10-2020
void CCodeParser::FindLocalVariables( std::vector<SFindDataResult<CFunction>>& oFunctionVector ) const
{
	for ( SFindDataResult<CFunction>& oFunction : oFunctionVector )
	{
		oFunction.oData.SetLocalVariables( FindLocalVariables( oFunction.oData ) );
	}
}

// ^^x
// std::string CCodeParser::PrepareFindGlobalFunctionRegexString
// 3BGO JIRA-238 06-10-2020
std::string CCodeParser::PrepareFindGlobalFunctionRegexString() const
{
	std::string oRegexPatternString{ FIND_FUNCTION_HEADER_INFORMATION_REGEX_STR };
	oRegexPatternString += FIND_GLOBAL_FUNCTION_HEADER_REGEX_STR;

	return oRegexPatternString;
}

// ^^x
// std::string CCodeParser::PrepareFindMemberFunctionRegexString
// 3BGO JIRA-238 06-10-2020
std::string CCodeParser::PrepareFindMemberFunctionRegexString() const
{
	std::string oRegexPatternString{ FIND_FUNCTION_HEADER_INFORMATION_REGEX_STR };
	oRegexPatternString += FIND_MEMBER_FUNCTION_HEADER_REGEX_STR;

	return oRegexPatternString;
}

// ^^x
// std::size_t CCodeParser::FindFunctionBracketOpenPosition
// 3BGO JIRA-238 02-10-2020
std::size_t CCodeParser::FindFunctionBracketOpenPosition( const std::string& oCodeString, const std::string& oFunctionNameString, const std::string::size_type uiCurrentCodeOffsetPos ) const
{
	const std::string::size_type uiFunctionHeaderBegPos = oCodeString.find( oFunctionNameString, uiCurrentCodeOffsetPos );
	const std::string::size_type uiFunctionHeaderEndPos = uiFunctionHeaderBegPos + oFunctionNameString.size();

	return oCodeString.find_first_of( '{', uiFunctionHeaderEndPos );
}

// ^^x
// std::size_t CCodeParser::FindFunctionBracketClosePosition
// 3BGO JIRA-238 02-10-2020
std::size_t CCodeParser::FindFunctionBracketClosePosition( const std::string& oCodeString, std::string::size_type uiCurrentCodeOffsetPos ) const
{
	std::string::size_type uiFunctionBracketLevel{ 1u };
	std::string::size_type uiSyntaxCharacterPos{ std::string::npos };

	bool bBeginCharacterLiteral{ false };
	bool bBeginStringLiteral{ false };

	while ( uiFunctionBracketLevel > 0u )
	{
		uiSyntaxCharacterPos = oCodeString.find_first_of( "{}'\"", uiCurrentCodeOffsetPos );

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
			
			uiCurrentCodeOffsetPos = uiSyntaxCharacterPos + 1u;
		}
		else
		{
			break;
		}
	}

	if ( uiFunctionBracketLevel > 0u )
	{
		uiCurrentCodeOffsetPos = std::string::npos;
	}

	return uiCurrentCodeOffsetPos;
}

// ^^x
// std::string CCodeParser::RetrieveBodyFunction
// 3BGO JIRA-238 10-10-2020
std::string CCodeParser::RetrieveBodyFunction( const std::string& oCodeString, const std::string& oFunctionHeaderString, std::string::size_type& uiCurrentCodeOffsetPos ) const
{
	std::string oFunctionBodyString{};

	const std::string oFunctionHeaderWithoutCommentsString = RemoveSingleLineComments( oFunctionHeaderString );
	const std::string oCodeWithoutCommentsString = RemoveSingleLineComments( oCodeString );
	const std::string::size_type uiFunctionBracketOpenPos = FindFunctionBracketOpenPosition( oCodeWithoutCommentsString, oFunctionHeaderWithoutCommentsString, uiCurrentCodeOffsetPos );
	
	if ( uiFunctionBracketOpenPos != std::string::npos )
	{
		uiCurrentCodeOffsetPos = uiFunctionBracketOpenPos + 1u;

		const std::string::size_type uiFunctionBracketClosePos = FindFunctionBracketClosePosition( oCodeWithoutCommentsString, uiCurrentCodeOffsetPos );
		if ( uiFunctionBracketClosePos != std::string::npos )
		{
			uiCurrentCodeOffsetPos = uiFunctionBracketClosePos;

			const std::string::size_type uiFunctionBodyLength = uiFunctionBracketClosePos - uiFunctionBracketOpenPos;
			oFunctionBodyString = oCodeWithoutCommentsString.substr( uiFunctionBracketOpenPos, uiFunctionBodyLength );

			++uiCurrentCodeOffsetPos;
		}
	}

	return oFunctionBodyString;
}

// ^^x
// std::string CCodeParser::SimplifyCode
// 3BGO JIRA-238 05-10-2020
std::string CCodeParser::SimplifyCode( const std::string& oCodeString ) const
{
	return CStringHelper::Replace( CStringHelper::SimplifyString( oCodeString ), '\n', ' ' );
}
