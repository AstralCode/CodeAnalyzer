#pragma once

#include "CodeFile.h"

struct SMemberFunctionDataset
{
	std::string oReturnTypeString{};
	std::string oClassNameString{};
	std::string oNameString{};
	std::string oArgListString{};
	std::string oModifierString{};
};

struct SFindMemberFunctionResult
{
	std::string oMatchString{};
	SMemberFunctionDataset oMemberFunctionDataset{};
};

class CSourceCodeFile final : public CCodeFile
{
public:
	CSourceCodeFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString );

	std::vector<SFindMemberFunctionResult> FindMemberFunctions() const;
};
