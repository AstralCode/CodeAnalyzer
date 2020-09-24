#include "DateTimeHelper.h"

#include <chrono>
#include <iomanip>
#include <sstream>

// ^^x
// std::string CDateTimeHelper::CurrentDate
// 3BGO JIRA-238 24-09-2020
std::string CDateTimeHelper::CurrentDate()
{
	const ::tm oDateTime = CurrentDateTime();

	std::stringstream oStringStream{};
	oStringStream << std::put_time( &oDateTime, "%F" );

	return oStringStream.str();
}

// ^^x
// std::string CDateTimeHelper::CurrentTime
// 3BGO JIRA-238 24-09-2020
std::string CDateTimeHelper::CurrentTime()
{
	const ::tm oDateTime = CurrentDateTime();

	std::stringstream oStringStream{};
	oStringStream << std::put_time( &oDateTime, "%T" );

	return oStringStream.str();
}

// ^^x
// std::tm CDateTimeHelper::CurrentDateTime
// 3BGO JIRA-238 24-09-2020
std::tm CDateTimeHelper::CurrentDateTime()
{
	const std::chrono::system_clock::time_point oCurrentTime = std::chrono::system_clock::now();
	const ::time_t oCurrentTimeT = std::chrono::system_clock::to_time_t( oCurrentTime );

	std::tm oDateTime{};
	localtime_s( &oDateTime, &oCurrentTimeT );

	return oDateTime;
}
