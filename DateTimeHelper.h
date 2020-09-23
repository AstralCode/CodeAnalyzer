#pragma once

#include <string>

class CDateTimeHelper final
{
public:
	static std::string currentDate();
	static std::string currentTime();

private:
	static std::tm currentDateTime();
};
