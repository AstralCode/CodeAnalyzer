#include "ConsoleInterface.h"

#include <iostream>
#include <iomanip>

#include "DateTimeHelper.h"

// ^^x
// void CConsoleInterface::Print
// 3BGO JIRA-238 01-10-2020
void CConsoleInterface::Print( std::string_view oMessageString, const EForegroundColor eForegroundColor )
{
	std::cout << "\033[" << static_cast<int>( eForegroundColor ) << "m" << oMessageString;
}

// ^^x
// void CConsoleInterface::PrintLine
// 3BGO JIRA-238 01-10-2020
void CConsoleInterface::PrintLine( std::string_view oMessageString, const bool bPrintTime, const EForegroundColor eForegroundColor )
{
	if ( bPrintTime )
	{
		std::cout << "\033[" << static_cast<int>( eForegroundColor ) << "m" << "<" + CDateTimeHelper::CurrentTime() + "> ";
	}

	std::cout << oMessageString << '\n';
}

// ^^x
// void CConsoleInterface::NewLine
// 3BGO JIRA-238 01-10-2020
void CConsoleInterface::NewLine()
{
	std::cout << '\n';
}

// ^^x
// void CConsoleInterface::ClearLine
// 3BGO JIRA-238 01-10-2020
void CConsoleInterface::ClearLine()
{
	std::cout << "\033[2K";
}
