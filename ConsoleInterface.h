#pragma once

#include <string>

class CConsoleInterface final
{
public:
	static void Print( std::string_view oMessageString );
	static void PrintLine( std::string_view oMessageString );
	static void PrintLineTime( std::string_view oMessageString );

	static void NewLine();
	static void ClearLine();
};
