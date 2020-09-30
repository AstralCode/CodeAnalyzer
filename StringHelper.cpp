#include "StringHelper.h"

#include <algorithm>
#include <iterator>

// ^^x
// std::string CStringHelper::SimplifyString
// 3BGO JIRA-239 30-09-2020
std::string CStringHelper::SimplifyString( const std::string& oInputString )
{
	std::string oResultString{};

	std::unique_copy( oInputString.cbegin(), oInputString.cend(), std::back_inserter( oResultString ), []( char cFirst, char cSecond )
					  {
						  return std::isspace( cFirst ) && std::isspace( cSecond );
					  } );

	std::replace( oResultString.begin(), oResultString.end(), '\n', ' ' );

	return oResultString;
}
