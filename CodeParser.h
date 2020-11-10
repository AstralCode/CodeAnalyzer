#pragma once

#include <map>
#include <vector>

#include "Function.h"

class CCodeParser final
{
public:
	CCodeParser() = default;

	CCodeParser( const CCodeParser& ) = delete;
	CCodeParser& operator=( const CCodeParser& ) = delete;

	std::size_t CountLines( const std::string& oCodeString ) const;

	std::vector<SFindDataResult<CFunction>> FindGlobalFunctionHeaders( const std::string& oCodeString ) const;
	std::vector<SFindDataResult<CFunction>> FindGlobalFunctions( const std::string& oCodeString ) const;

	std::vector<SFindDataResult<CFunction>> FindMemberFunctionHeaders( const std::string& oCodeString ) const;
	std::vector<SFindDataResult<CFunction>> FindMemberFunctions( const std::string& oCodeString ) const;

	std::vector<SFindDataResult<CVariable>> FindGlobalVariables( const std::string& oCodeString ) const;
	std::vector<SFindDataResult<CVariable>> FindLocalVariables( const CFunction& oFunction ) const;
	std::vector<SFindDataResult<CVariable>> FindVariables( const std::string& oCodeString ) const;

	void RemoveMultiLineComments( std::string& oCodeString ) const;
	void RemoveSingleLineComments( std::string& oCodeString ) const;
	void RemoveDirectives( std::string& oCodeString ) const;
	void RemoveMacros( std::string& oCodeString ) const;
	void RemoveStatemets( std::string& oCodeString ) const;
	void RemoveMemberDataListInitialization( std::string& oCodeString ) const;
	void RemoveMemberFunctionBodies( std::string& oCodeString ) const;
	void RemoveDeclarations( std::string& oCodeString ) const;

private:
	void RetrieveBodyFunctions( const std::string& oCodeString, std::vector<SFindDataResult<CFunction>>& oFunctionVector ) const;
	void FindLocalVariables( std::vector<SFindDataResult<CFunction>>& oFunctionVector ) const;

	void RemoveMatches( std::string& oCodeString, const char* szRegexPattern ) const;

	std::string PrepareFindGlobalFunctionRegexString() const;
	std::string PrepareFindMemberFunctionRegexString() const;

	std::size_t FindFunctionBracketOpenPosition( const std::string& oCodeString, const std::string& oFunctionHeaderString, const std::string::size_type uiCurrentCodeOffsetPos ) const;
	std::size_t FindFunctionBracketClosePosition( const std::string& oCodeString, std::string::size_type uiCurrentCodeOffsetPos ) const;

	std::string RetrieveBodyFunction( const std::string& oCodeString, const std::string& oFunctionNameString, std::string::size_type& uiCurrentCodeOffsetPos ) const;

	std::string SimplifyCode( const std::string& oCodeString ) const;
};
