#pragma once

#include <filesystem>
#include <optional>

struct SCommandLineArgumentDataset
{
	std::filesystem::path oInputDirectoryPath;
	std::filesystem::path oOutputDirectoryPath;
	std::optional<std::string> oDeveloperString;
	std::optional<std::string> oReportPrefixNameString;
	std::optional<std::string> oReportDataSeparatorString;
};
