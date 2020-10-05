#pragma once

#include <string>
#include <optional>

struct SMemberFunctionHeaderDataset
{
	std::optional<std::string> oAuthorString{};
	std::optional<std::string> oInformationString{};
	std::string oHeaderString{};
	std::string oReturnTypeString{};
	std::string oClassNameString{};
	std::string oNameString{};
	std::optional<std::string> oArgumentsString{};
	std::optional<std::string> oModifierString{};
	std::string oBodyString{};
};
