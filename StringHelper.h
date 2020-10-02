#pragma once

#include <string>
#include <vector>

class CStringHelper final
{
public:
	static std::string SimplifyString( const std::string& oInputString );

	static std::string Replace( const std::string& oInputString, const char cOld, const char cNew );

	static std::vector<std::string> SplitLines( const std::string& oInputString );
};
