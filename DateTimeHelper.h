#pragma once

#include <string>

class CDateTimeHelper final
{
public:
	static std::string CurrentDate();
	static std::string CurrentTime();

private:
	static std::tm CurrentDateTime();
};
