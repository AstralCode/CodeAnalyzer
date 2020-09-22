#pragma once

#include <string>
#include <filesystem>

class COSLayerHelper final
{
public:
	static std::string currentDate();
	static std::string currentTime();

	static bool createDirectory( const std::filesystem::path path );
	static bool isFileExists( const std::filesystem::path path );

private:
	static std::tm currentDateTime();
};
