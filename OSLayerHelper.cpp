#include "OSLayerHelper.h"

#include <chrono>
#include <iomanip>
#include <sstream>

std::string COSLayerHelper::currentDate()
{
	const auto dateTime = currentDateTime();

	std::stringstream stringStream{};
	stringStream << std::put_time( &dateTime, "%F" );

	return stringStream.str();
}

std::string COSLayerHelper::currentTime()
{
	const auto dateTime = currentDateTime();

	std::stringstream stringStream{};
	stringStream << std::put_time( &dateTime, "%T" );

	return stringStream.str();
}

bool COSLayerHelper::createDirectory( const std::filesystem::path path )
{
	return std::filesystem::create_directories( path );
}

bool COSLayerHelper::isFileExists( const std::filesystem::path path )
{
	return std::filesystem::exists( path );
}

std::tm COSLayerHelper::currentDateTime()
{
	const auto currentTime = std::chrono::system_clock::now();
	const auto currentTimeT = std::chrono::system_clock::to_time_t( currentTime );

	std::tm dateTime{};
	localtime_s( &dateTime, &currentTimeT );

	return dateTime;
}
