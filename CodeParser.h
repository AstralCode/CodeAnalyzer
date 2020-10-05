#pragma once

#include <vector>

#include "MemberFunctionDataset.h"

class CCodeParser final
{
public:
	CCodeParser() = default;

	CCodeParser( const CCodeParser& ) = delete;
	CCodeParser& operator=( const CCodeParser& ) = delete;

	std::vector<SMemberFunctionHeaderDataset> FindMemberFunctionHeaders( const std::string oCodeString ) const;
	std::vector<SMemberFunctionHeaderDataset> FindMemberFunctionHeadersDetails( const std::string oCodeString ) const;
	std::vector<SMemberFunctionHeaderDataset> FindMemberFunctions( const std::string oCodeString, const bool bFindHeaderDetails = false ) const;

	std::string RemoveSingleLineComments( const std::string& oCodeString ) const;
	std::string RemoveMultilineComments( const std::string& oCodeString ) const;

private:
	std::size_t FindFunctionBracketOpenPosition( const std::string& oCodeString, const std::string& oFunctionHeaderString, const std::size_t uiCurrentSearchOffsetPos ) const;
	std::size_t FindFunctionBracketClosePosition( const std::string& oCodeString, std::size_t uiCurrentSearchOffsetPos ) const;

	std::string RetrieveBodyFunction( const std::string& oCodeString, const std::size_t uiFunctionBracketOpenPos, const std::size_t uiFunctionBracketClosePos ) const;
};
