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
	std::string oHeaderString{};
};

struct SFindMemberFunctionHeaderDetailResult
{
	SFindMemberFunctionHeaderResult oHeaderResult{};
	SMemberFunctionHeaderDataset oHeaderDataset{};
};

struct SFindMemberFunctionResult
{
	SFindMemberFunctionHeaderResult oHeaderResult{};
	SMemberFunctionBodyDataset oBodyDataset{};
};

struct SFindMemberFunctionDetailResult
{
	SFindMemberFunctionHeaderResult oHeaderResult{};
	SMemberFunctionHeaderDataset oHeaderDataset{};
	SMemberFunctionBodyDataset oBodyDataset{};
};

class CCodeParser final
{
public:
	CCodeParser() = default;

	CCodeParser( const CCodeParser& ) = delete;
	CCodeParser& operator=( const CCodeParser& ) = delete;

	std::vector<SFindMemberFunctionHeaderResult> FindMemberFunctionHeaders( const CCodeFile& oCodeFile ) const;
	std::vector<SFindMemberFunctionHeaderDetailResult> FindMemberFunctionHeadersDetails( const CCodeFile& oCodeFile ) const;
	std::vector<SFindMemberFunctionResult> FindMemberFunctions( const CCodeFile& oCodeFile ) const;
	std::vector<SFindMemberFunctionDetailResult> FindMemberFunctionsDetails( const CCodeFile& oCodeFile ) const;
};
