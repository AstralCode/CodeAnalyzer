#pragma once

#include <vector>

#include "Function.h"
#include "FindDataResult.h"

class CCodeParser final
{
public:
	CCodeParser() = default;

	CCodeParser( const CCodeParser& ) = delete;
	CCodeParser& operator=( const CCodeParser& ) = delete;

	unsigned int CountLines( const std::string& oCodeString ) const;

	std::vector<SFindDataResult<CFunction>> FindGlobalFunctionHeaders( const std::string& oCodeString ) const;
	std::vector<SFindDataResult<CFunction>> FindGlobalFunctions( const std::string& oCodeString ) const;

	std::vector<SFindDataResult<CFunction>> FindMemberFunctionHeaders( const std::string& oCodeString ) const;
	std::vector<SFindDataResult<CFunction>> FindMemberFunctions( const std::string& oCodeString ) const;

	std::string RemoveSingleLineComments( const std::string& oCodeString ) const;
	std::string RemoveMultilineComments( const std::string& oCodeString ) const;
	std::string RemoveIncludeDirectives( const std::string& oCodeString ) const;
	std::string RemoveImplementDynamicMacro( const std::string& oCodeString ) const;
	std::string RemoveImplementDyncreateMacro( const std::string& oCodeString ) const;
	std::string RemoveMessageMapMacro( const std::string& oCodeString ) const;

	std::string RemoveMemberDataListInitialization( const std::string& oCodeString ) const;
	std::string RemoveMemberFunctionBodies( const std::string& oCodeString ) const;

private:
	void RetrieveBodyFunctions( const std::string& oCodeString, std::vector<SFindDataResult<CFunction>>& oMemberFunctionVector ) const;

	std::string PrepareFindGlobalFunctionRegexString() const;
	std::string PrepareFindMemberFunctionRegexString() const;

	std::size_t FindFunctionBracketOpenPosition( const std::string& oCodeString, const std::string& oFunctionHeaderString, const std::string::size_type uiCurrentCodeOffsetPos ) const;
	std::size_t FindFunctionBracketClosePosition( const std::string& oCodeString, std::string::size_type uiCurrentCodeOffsetPos ) const;

	std::string RetrieveBodyFunction( const std::string& oCodeString, const std::string& oFunctionNameString, std::string::size_type& uiCurrentCodeOffsetPos ) const;

	std::string SimplifyCode( const std::string& oCodeString ) const;
};
