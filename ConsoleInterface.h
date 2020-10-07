#pragma once

#include <string>

class CConsoleInterface final
{
public:
	enum class EForegroundColor
	{
		eBlack = 30,
		eRed = 31,
		eGreen = 32,
		eYellow = 33,
		eBlue = 34,
		eMagenta = 35,
		eCyan = 36,
		eWhite = 37
	};

	enum class EBackgroundColor
	{
		eBlack = 40,
		eRed = 41,
		eGreen = 42,
		eYellow = 43,
		eBlue = 44,
		eMagenta = 45,
		eCyan = 46,
		eWhite = 47,
	};

	static void Print( std::string_view oMessageString, const EForegroundColor eForegroundColor = EForegroundColor::eWhite );
	static void PrintLine( std::string_view oMessageString, const EForegroundColor eForegroundColor = EForegroundColor::eWhite );
	static void PrintLineTime( std::string_view oMessageString, const EForegroundColor eForegroundColor = EForegroundColor::eWhite );

	static void NewLine();
	static void ClearLine();
};
