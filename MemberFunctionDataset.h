#pragma once

#include <string>
#include <optional>

struct SMemberFunctionDataset
{
	std::optional<std::string> oAuthorString;
	std::optional<std::string> oInformationString;
	std::string oHeaderString;
	std::string oReturnTypeString;
	std::string oClassNameString;
	std::string oNameString;
	std::optional<std::string> oArgumentsString;
	std::string oBodyString;
};
