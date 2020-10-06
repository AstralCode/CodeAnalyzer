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

	static void Flush();
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
// void CConsoleInterface::ProcessHeaderFile
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
	printf( "\r                                                                                                                \r" );
}

// ^^x
// void CConsoleInterface::Flush
// 3BGO JIRA-238 01-10-2020
inline void CConsoleInterface::Flush()
{
	std::cout << std::flush;
}
