#pragma once

#include <string>
#include <vector>

class CStringHelper final
{
public:
	static std::string SimplifyString( std::string_view oInputString );

	static std::string Replace( std::string_view oInputString, const char cOld, const char cNew );
	static std::string Replace( std::string_view oInputString, std::string_view oOldString, std::string_view oNewString );

	static std::string ToLowerCase( std::string_view oInputString );

	static std::vector<std::string> SplitLines( std::string_view oInputString );
};
