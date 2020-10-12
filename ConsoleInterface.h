#pragma once

#include <string>

class CConsoleInterface final
{
public:
	static void Print( const std::string& oMessageString );
	static void PrintLine( const std::string& oMessageString );
	static void PrintLineTime( const std::string& oMessageString );

	static void NewLine();
	static void ClearLine();
};
