#pragma once

#include "CodeFile.h"

struct SMemberFunctionHeaderDataset
{
	std::string oAuthorString{};
	std::string oInformationString{};
	std::string oReturnTypeString{};
	std::string oClassNameString{};
	std::string oNameString{};
	std::string oArgumentsString{};
	std::string oModifierString{};
};

struct SMemberFunctionBodyDataset
{
	std::string oBodyString{};
};

struct SFindMemberFunctionHeaderResult
{
	std::string oMatchString{};
};

struct SFindMemberFunctionHeaderDetailResult
{
	std::string oMatchString{};
	SMemberFunctionHeaderDataset oMemberFunctionHeaderDataset{};
};

struct SFindMemberFunctionBodyResult
{
	std::string oMathString{};
	SMemberFunctionBodyDataset oMemberFunctionBodyDataset{};
};

class CSourceCodeFile final : public CCodeFile
{
public:
	CSourceCodeFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString );

	std::vector<SFindMemberFunctionHeaderResult> FindMemberFunctionHeader() const;
	std::vector<SFindMemberFunctionHeaderDetailResult> FindMemberFunctionHeaderDetails() const;
	std::vector<SFindMemberFunctionBodyResult> FindMemberFunctionBodies() const;
};
