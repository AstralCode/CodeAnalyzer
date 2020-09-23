#include "DateTimeHelper.h"

#include <chrono>
#include <iomanip>
#include <sstream>

std::string CDateTimeHelper::currentDate()
{
	const auto dateTime = currentDateTime();

	std::stringstream stringStream{};
	stringStream << std::put_time( &dateTime, "%F" );

	return stringStream.str();
}

std::string CDateTimeHelper::currentTime()
{
	const auto dateTime = currentDateTime();

	std::stringstream stringStream{};
	stringStream << std::put_time( &dateTime, "%T" );

	return stringStream.str();
}

std::tm CDateTimeHelper::currentDateTime()
{
	const auto currentTime = std::chrono::system_clock::now();
	const auto currentTimeT = std::chrono::system_clock::to_time_t( currentTime );

	std::tm dateTime{};
	localtime_s( &dateTime, &currentTimeT );

	return dateTime;
}
