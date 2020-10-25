#pragma once

#include <string>

class CConsoleInterface final
{
public:
	static void Print( const std::string& oMessageString, const bool bPrintTime = false );
	static void PrintLine( const std::string& oMessageString, const bool bPrintTime = false );

	static void NewLine();
	static void ClearLine();
};
