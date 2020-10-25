#include "ConsoleInterface.h"

#include <iostream>
#include <iomanip>

#include "DateTimeHelper.h"

// ^^x
// void CConsoleInterface::Print
// 3BGO JIRA-238 01-10-2020
void CConsoleInterface::Print( const std::string& oMessageString, const bool bPrintTime )
{
	if ( bPrintTime )
	{
		std::cout << "<" + CDateTimeHelper::CurrentTime() + "> ";
	}

	std::cout << oMessageString;
}

// ^^x
// void CConsoleInterface::PrintLine
// 3BGO JIRA-238 01-10-2020
void CConsoleInterface::PrintLine( const std::string& oMessageString, const bool bPrintTime )
{
	if ( bPrintTime )
	{
		std::cout << "<" + CDateTimeHelper::CurrentTime() + "> ";
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
	std::cout << '\r' << std::setw( 100 ) << ' ' << '\r';
}
