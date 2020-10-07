#pragma once

#include <string>
#include <vector>

class CStringHelper final
{
public:
	static std::string SimplifyString( const std::string_view& oInputString );

	static std::string Replace( const std::string_view& oInputString, const char cOld, const char cNew );
	static std::string Replace( const std::string_view& oInputString, const std::string_view& oOldString, const std::string_view& oNewString );

	static std::string ToLowerCase( const std::string_view& oInputString );

	static std::vector<std::string> SplitLines( const std::string_view& oInputString );
};
