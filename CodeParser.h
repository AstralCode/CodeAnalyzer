#pragma once

#include <vector>

#include "MemberFunctionDataset.h"

class CCodeParser final
{
public:
	CCodeParser() = default;

	CCodeParser( const CCodeParser& ) = delete;
	CCodeParser& operator=( const CCodeParser& ) = delete;

	std::vector<SMemberFunctionHeaderDataset> FindMemberFunctionHeaders( const std::string oCodeString, std::optional<std::string> oDeveloperString ) const;
	std::vector<SMemberFunctionHeaderDataset> FindMemberFunctions( const std::string oCodeString, std::optional<std::string> oDeveloperString ) const;

	std::string RemoveSingleLineComments( const std::string& oCodeString ) const;
	std::string RemoveMultilineComments( const std::string& oCodeString ) const;

private:
	std::string PrepareFindMemberFunctionHeaderRegexString( std::optional<std::string> oDeveloperString ) const;
	std::string PrepareFindMemberFunctionRegexString( std::optional<std::string> oDeveloperString ) const;

	std::size_t FindFunctionBracketOpenPosition( const std::string& oCodeString, const std::string& oFunctionHeaderString, const std::size_t uiCurrentSearchOffsetPos ) const;
	std::size_t FindFunctionBracketClosePosition( const std::string& oCodeString, std::size_t uiCurrentSearchOffsetPos ) const;

	std::string RetrieveBodyFunction( const std::string& oCodeString, const std::size_t uiFunctionBracketOpenPos, const std::size_t uiFunctionBracketClosePos ) const;

	std::string SimplifyCode( const std::string& oCodeString ) const;

	std::string CreateGroupRegexString( const std::string& oRegexString, bool bCapturingGroup = true, bool bOptionalGroup = false ) const;
};
