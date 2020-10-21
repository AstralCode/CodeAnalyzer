#include "CodeParser.h"

#include <regex>

#include "CodeFile.h"
#include "RegexPatterns.h"
#include "StringHelper.h"

// ^^x
// std::size_t CCodeParser::CountLines
// 3BGO JIRA-238 02-10-2020
std::size_t CCodeParser::CountLines( const std::string& oCodeString ) const
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
	std::string oModifiedCodeString = oCodeString;
	RemoveMemberFunctionBodies( oModifiedCodeString );

	std::vector<SFindDataResult<CFunction>> oGlobalFunctionVector = FindGlobalFunctionHeaders( oModifiedCodeString );
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
	std::regex oRegexPattern{ RegexPatterns::SZ_RGX_VARIABLE };

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
// void CCodeParser::RemoveMultiLineComments
// 3BGO JIRA-238 02-10-2020
void CCodeParser::RemoveMultiLineComments( std::string& oCodeString ) const
{
	oCodeString = CStringHelper::RemoveBetween( oCodeString, "/*", "*/" );
}

// ^^x
// void CCodeParser::RemoveSingleLineComments
// 3BGO JIRA-238 02-10-2020
void CCodeParser::RemoveSingleLineComments( std::string& oCodeString ) const
{
	RemoveMatches( oCodeString, RegexPatterns::SZ_RGX_COMMENT_SINGLELINE );
}

// ^^x
// void CCodeParser::RemoveDirectives
// 3BGO JIRA-238 02-10-2020
void CCodeParser::RemoveDirectives( std::string& oCodeString ) const
{
	RemoveMatches( oCodeString, RegexPatterns::SZ_RGX_DIRECTIVE_INCLUDE );
}

// ^^x
// void CCodeParser::RemoveMacros
// 3BGO JIRA-238 02-10-2020
void CCodeParser::RemoveMacros( std::string& oCodeString ) const
{
	RemoveMatches( oCodeString, RegexPatterns::SZ_RGX_MACRO_IMPLEMENT_DYNAMIC );
	RemoveMatches( oCodeString, RegexPatterns::SZ_RGX_MACRO_IMPLEMENT_DYNCREATE );

	oCodeString = CStringHelper::RemoveBetween( oCodeString, "BEGIN_MESSAGE_MAP", "END_MESSAGE_MAP()" );
}

// ^^x
// void CCodeParser::RemoveStatemets
// 3BGO JIRA-238 02-10-2020
void CCodeParser::RemoveStatemets( std::string& oCodeString ) const
{
	oCodeString = CStringHelper::Remove( oCodeString, R"('{')" );
	oCodeString = CStringHelper::Remove( oCodeString, R"('}')" );
	oCodeString = CStringHelper::Remove( oCodeString, R"('"')" );
	oCodeString = CStringHelper::Remove( oCodeString, R"(\")" );
	oCodeString = CStringHelper::Remove( oCodeString, R"(')" );
	oCodeString = CStringHelper::RemoveBetween( oCodeString, R"!(R"()!", R"!()")!" );
	oCodeString = CStringHelper::RemoveBetween( oCodeString, R"(")", R"(")", true );
	oCodeString = CStringHelper::Remove( oCodeString, R"(\)" );
}

// ^^x
// void CCodeParser::RemoveMemberDataListInitialization
// 3BGO JIRA-238 02-10-2020
void CCodeParser::RemoveMemberDataListInitialization( std::string& oCodeString ) const
{
	RemoveMatches( oCodeString, RegexPatterns::SZ_RGX_MEMBER_DATA_LIST_INITIALIZATION );
}

// ^^x
// void CCodeParser::RemoveMemberFunctionBodies
// 3BGO JIRA-238 02-10-2020
void CCodeParser::RemoveMemberFunctionBodies( std::string& oCodeString ) const
{
	RemoveSingleLineComments( oCodeString );

	std::string::size_type uiCurrentCodeOffsetPos{ 0u };

	const std::vector<SFindDataResult<CFunction>> oMemberFunctionVector = FindMemberFunctions( oCodeString );
	for ( const SFindDataResult<CFunction>& oMemberFunction : oMemberFunctionVector )
	{
		const std::string::size_type uiMemberFunctionBodyBegPos = oCodeString.find( *oMemberFunction.oData.GetBody(), uiCurrentCodeOffsetPos );
		if ( uiMemberFunctionBodyBegPos != std::string::npos )
		{
			oCodeString.erase( uiMemberFunctionBodyBegPos, oMemberFunction.oData.GetBody()->size() );
			uiCurrentCodeOffsetPos = uiMemberFunctionBodyBegPos;
		}
	}
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
// void CCodeParser::RemoveMatches
// 3BGO JIRA-238 12-10-2020
void CCodeParser::RemoveMatches( std::string& oCodeString, const char* szRegexPattern ) const
{
	if ( szRegexPattern != nullptr )
	{
		oCodeString = std::regex_replace( oCodeString, std::regex{ szRegexPattern }, "" );
	}
}

// ^^x
// std::string CCodeParser::PrepareFindGlobalFunctionRegexString
// 3BGO JIRA-238 06-10-2020
std::string CCodeParser::PrepareFindGlobalFunctionRegexString() const
{
	std::string oRegexPatternString{ RegexPatterns::SZ_RGX_FUNCTION_HEADER_INFORMATION };
	oRegexPatternString += RegexPatterns::SZ_RGX_GLOBAL_FUNCTION_HEADER;

	return oRegexPatternString;
}

// ^^x
// std::string CCodeParser::PrepareFindMemberFunctionRegexString
// 3BGO JIRA-238 06-10-2020
std::string CCodeParser::PrepareFindMemberFunctionRegexString() const
{
	std::string oRegexPatternString{ RegexPatterns::SZ_RGX_FUNCTION_HEADER_INFORMATION };
	oRegexPatternString += RegexPatterns::SZ_RGX_MEMBER_FUNCTION_HEADER;

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

	while ( uiFunctionBracketLevel > 0u && uiCurrentCodeOffsetPos < std::string::npos )
	{
		const std::string::size_type uiSyntaxCharacterPos = oCodeString.find_first_of( "{}", uiCurrentCodeOffsetPos );
		uiCurrentCodeOffsetPos = uiSyntaxCharacterPos;

		if ( uiSyntaxCharacterPos != std::string::npos )
		{
			if ( oCodeString[uiSyntaxCharacterPos] == '{' )
			{
				++uiFunctionBracketLevel;
			}
			else if ( oCodeString[uiSyntaxCharacterPos] == '}' )
			{
				--uiFunctionBracketLevel;
			}

			++uiCurrentCodeOffsetPos;
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

	std::string oModifiedCodeString = oCodeString;
	RemoveSingleLineComments( oModifiedCodeString );

	std::string oModifiedFunctionHeaderString = oFunctionHeaderString;
	RemoveSingleLineComments( oModifiedFunctionHeaderString );
	
	const std::string::size_type uiFunctionBracketOpenPos = FindFunctionBracketOpenPosition( oModifiedCodeString, oModifiedFunctionHeaderString, uiCurrentCodeOffsetPos );
	
	if ( uiFunctionBracketOpenPos != std::string::npos )
	{
		uiCurrentCodeOffsetPos = uiFunctionBracketOpenPos + 1u;

		const std::string::size_type uiFunctionBracketClosePos = FindFunctionBracketClosePosition( oModifiedCodeString, uiCurrentCodeOffsetPos );
		if ( uiFunctionBracketClosePos != std::string::npos )
		{
			uiCurrentCodeOffsetPos = uiFunctionBracketClosePos;

			const std::string::size_type uiFunctionBodyLength = uiFunctionBracketClosePos - uiFunctionBracketOpenPos;
			oFunctionBodyString = oModifiedCodeString.substr( uiFunctionBracketOpenPos, uiFunctionBodyLength );

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
