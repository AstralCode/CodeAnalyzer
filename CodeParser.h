#pragma once

#include <string>
#include <vector>

class CCodeFile;

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

class CCodeParser final
{
public:
	CCodeParser() = default;

	CCodeParser( const CCodeParser& ) = delete;
	CCodeParser& operator=( const CCodeParser& ) = delete;

	std::vector<SFindMemberFunctionHeaderResult> FindMemberFunctionHeader( const CCodeFile& oCodeFile ) const;
	std::vector<SFindMemberFunctionHeaderDetailResult> FindMemberFunctionHeaderDetails( const CCodeFile& oCodeFile ) const;
};
