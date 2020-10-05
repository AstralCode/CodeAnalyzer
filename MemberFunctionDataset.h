#pragma once

#include <string>
#include <optional>

struct SMemberFunctionHeaderDataset
{
	std::string oHeaderString{};
	std::optional<std::string> oAuthorString{};
	std::optional<std::string> oInformationString{};
	std::optional<std::string> oReturnTypeString{};
	std::optional<std::string> oClassNameString{};
	std::optional<std::string> oNameString{};
	std::optional<std::string> oArgumentsString{};
	std::optional<std::string> oModifierString{};
	std::optional<std::string> oBodyString{};
};
