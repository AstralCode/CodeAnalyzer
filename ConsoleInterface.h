#pragma once

#include <string>
#include <iostream>

class CConsoleInterface final
{
public:
	template <typename T>
	static void Print( T&& oOutputT );
	template <typename T>
	static void PrintLine( T&& oOutputT );

	static void NewLine();
	static void ClearLine();
};

// ^^x
// void CConsoleInterface::Print
// 3BGO JIRA-238 01-10-2020
template <typename T>
inline void CConsoleInterface::Print( T&& oOutputT )
{
	std::cout << std::forward<T>( oOutputT );
}

// ^^x
// void CConsoleInterface::ProcessFile
// 3BGO JIRA-238 01-10-2020
template <typename T>
inline void CConsoleInterface::PrintLine( T&& oOutputT )
{
	Print( std::forward<T>( oOutputT ) );
	Print( '\n' );
}

// ^^x
// void CConsoleInterface::NewLine
// 3BGO JIRA-238 01-10-2020
inline void CConsoleInterface::NewLine()
{
	Print( '\n' );
}

// ^^x
// void CConsoleInterface::ClearLine
// 3BGO JIRA-238 01-10-2020
inline void CConsoleInterface::ClearLine()
{
	printf( "%c[2K", 27 );
	Print( '\r' );
}
