 #include "StringHelper.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <locale>

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
// std::string CStringHelper::Replace
// 3BGO JIRA-238 02-10-2020
std::string CStringHelper::Replace( const std::string& oInputString, const std::string& oOldString, const std::string& oNewString )
{
	std::string oResultString{ oInputString };

	const std::size_t uiOldStringPos = oResultString.find( oOldString );

	if ( uiOldStringPos != std::string::npos )
	{
		oResultString.replace( uiOldStringPos, oOldString.length(), oNewString );
	}

	return oResultString;
}

// ^^x
// std::string CStringHelper::Remove
// 3BGO JIRA-238 06-10-2020
std::string CStringHelper::Remove( const std::string& oInputString, const std::string& oSubString )
{
	std::string oResultString{ oInputString };
	std::string::size_type uiCurrentOffsetPos{ 0u };

	do
	{
		const std::string::size_type uiBegPos = oResultString.find( oSubString, uiCurrentOffsetPos );
		if ( uiBegPos == std::string::npos )
		{
			break;
		}

		oResultString.erase( uiBegPos, oSubString.size() );
		uiCurrentOffsetPos = uiBegPos;
	}
	while ( true );

	return oResultString;
}

// ^^x
// std::string CStringHelper::RemoveBetween
// 3BGO JIRA-238 06-10-2020
std::string CStringHelper::RemoveBetween( const std::string& oInputString, const std::string& oLeftString, const std::string& oRightString, bool bSameLine )
{
	std::string oResultString = oInputString;

	std::string::size_type uiCurrentOffsetPos{ 0u };

	while ( uiCurrentOffsetPos < oResultString.size() )
	{
		const std::string::size_type uiBegPos = oResultString.find( oLeftString, uiCurrentOffsetPos );
		uiCurrentOffsetPos = uiBegPos;

		if ( uiBegPos != std::string::npos )
		{
			uiCurrentOffsetPos += oLeftString.size();

			std::string::size_type uiEndPos = oResultString.find( oRightString, uiCurrentOffsetPos );
			
			if ( bSameLine )
			{
				const std::string::size_type uiNewLinePos = oResultString.find( "\n", uiCurrentOffsetPos );
				uiCurrentOffsetPos = uiEndPos;
				uiEndPos = ( uiNewLinePos < uiEndPos ) ? std::string::npos : uiEndPos;
			}

			if ( uiEndPos != std::string::npos )
			{
				const std::string::size_type uiLength = ( uiEndPos - uiBegPos ) + oRightString.size();
				
				oResultString.erase( uiBegPos, uiLength );
				uiCurrentOffsetPos = uiBegPos;
			}
		}
	}

	return oResultString;
}

// ^^x
// std::string CStringHelper::ToLowerCase
// 3BGO JIRA-238 06-10-2020
std::string CStringHelper::ToLowerCase( const std::string& oInputString )
{
	std::string oResultString{ oInputString };
	std::locale oLocale{};

	std::transform( oInputString.cbegin(), oInputString.cend(), oResultString.begin(), [oLocale]( const unsigned char cCharacter )
	{
		return std::tolower( cCharacter, oLocale );
	} );

	return oResultString;
}

// ^^x
// std::string CStringHelper::TrimLeft
// 3BGO JIRA-238 22-10-2020
std::string CStringHelper::TrimLeft( const std::string& oInputString )
{
	std::string oResultString{ oInputString };

	const std::string::const_iterator oStringIt = std::find_if( oResultString.cbegin(), oResultString.cend(), []( const unsigned char cCharacter )
	{
		return !std::isspace( cCharacter );
	} );

	oResultString.erase( oResultString.cbegin(), oStringIt );

	return oResultString;
}

// ^^x
// std::string CStringHelper::TrimRight
// 3BGO JIRA-238 22-10-2020
std::string CStringHelper::TrimRight( const std::string& oInputString )
{
	std::string oResultString{ oInputString };

	const std::string::const_iterator oStringIt = std::find_if( oResultString.crbegin(), oResultString.crend(), []( const unsigned char cCharacter )
	{
		return !std::isspace( cCharacter );
	} ).base();

	oResultString.erase( oStringIt, oResultString.cend() );

	return oResultString;
}

// ^^x
// std::string CStringHelper::Trim
// 3BGO JIRA-238 22-10-2020
std::string CStringHelper::Trim( const std::string& oInputString )
{
	return TrimRight( TrimLeft( oInputString ) );
}

// ^^x
// std::vector<std::string> CStringHelper::Split
// 3BGO JIRA-238 22-10-2020
std::vector<std::string> CStringHelper::Split( const std::string& oInputString, const char cDelimiter )
{
	std::vector<std::string> oLineVector{};

	std::istringstream oStringStream{ oInputString };
	std::string oLineString{};

	while ( std::getline( oStringStream, oLineString, cDelimiter ) )
	{
		oLineVector.push_back( oLineString );
	}

	return oLineVector;
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
