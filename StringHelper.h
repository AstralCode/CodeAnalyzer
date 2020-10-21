#pragma once

#include <string>
#include <vector>

class CStringHelper final
{
public:
	static std::string SimplifyString( const std::string& oInputString );

	static std::string Replace( const std::string& oInputString, const char cOld, const char cNew );
	static std::string Replace( const std::string& oInputString, const std::string& oOldString, const std::string& oNewString );

	static std::string Remove( const std::string& oInputString, const std::string& oSubString );
	static std::string RemoveBetween( const std::string& oInputString, const std::string& oLeftString, const std::string& oRightString, bool bSameLine = false );

	static std::string ToLowerCase( const std::string& oInputString );

	static std::vector<std::string> SplitLines( const std::string& oInputString );
};
