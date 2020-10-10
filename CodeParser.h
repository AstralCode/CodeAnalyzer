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

	unsigned int CountLines( std::string_view oCodeString ) const;

	std::vector<SFindDataResult<CFunction>> FindMemberFunctionHeaders( std::string_view oCodeString ) const;
	std::vector<SFindDataResult<CFunction>> FindMemberFunctions( std::string_view oCodeString ) const;

	std::string RemoveSingleLineComments( std::string_view oCodeString ) const;
	std::string RemoveMultilineComments( std::string_view oCodeString ) const;

	std::string RemoveMemberDataListInitialization( std::string_view oCodeString ) const;

private:
	std::string PrepareFindMemberFunctionRegexString() const;

	std::size_t FindFunctionBracketOpenPosition( std::string_view oCodeString, std::string_view oFunctionHeaderString, const std::size_t uiCurrentSearchOffsetPos ) const;
	std::size_t FindFunctionBracketClosePosition( std::string_view oCodeString, std::size_t uiCurrentSearchOffsetPos ) const;

	std::string_view RetrieveBodyFunction( std::string_view oCodeString, const std::size_t uiFunctionBracketOpenPos, const std::size_t uiFunctionBracketClosePos ) const;

	std::string SimplifyCode( std::string_view oCodeString ) const;
};
