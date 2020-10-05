#include "StringHelper.h"

#include <algorithm>
#include <iterator>
#include <sstream>

// ^^x
// std::string CStringHelper::SimplifyString
// 3BGO JIRA-238 30-09-2020
std::string CStringHelper::SimplifyString( const std::string& oInputString )
{
	std::string oResultString{};

	std::unique_copy( oInputString.cbegin(), oInputString.cend(), std::back_inserter( oResultString ), []( char cFirst, char cSecond )
	{
		return std::isspace( cFirst ) && std::isspace( cSecond );
	} );

	return oResultString;
}

// ^^x
// std::string CStringHelper::Replace
// 3BGO JIRA-238 02-10-2020
std::string CStringHelper::Replace( const std::string& oInputString, const char cOld, const char cNew )
{
	std::string oResultString{ oInputString };

	std::replace( oResultString.begin(), oResultString.end(), cOld, cNew );

	return oResultString;
}

// ^^x
// std::vector<std::string> CStringHelper::SplitLines
// 3BGO JIRA-238 02-10-2020
std::vector<std::string> CStringHelper::SplitLines( const std::string& oInputString )
{
	std::vector<std::string> oLineVector{};

	std::istringstream oStringStream{ oInputString };
	std::string oLineString{};

	while ( std::getline( oStringStream, oLineString ) )
	{
		oLineVector.push_back( oLineString );
	}

	return oLineVector;
}
