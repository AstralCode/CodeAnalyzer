#pragma once

#include <filesystem>
#include <optional>

struct SCommandLineArgumentDataset
{
	std::filesystem::path oInputDirectoryPath;
	std::optional<std::string> oReportPrefixNameString;
	std::optional<std::string> oDeveloperString;
};
