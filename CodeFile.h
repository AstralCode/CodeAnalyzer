#pragma once

#include <filesystem>
#include <vector>

#include "MemberFunctionDataset.h"

class CCodeFile final
{
public:
	enum class EType
	{
		eUnknown,
		eHeader,
		eSource
	};

	CCodeFile( const std::filesystem::path& oPath, const std::string& oContentString, const EType eType );

	CCodeFile( const CCodeFile& ) = delete;
	CCodeFile& operator=( const CCodeFile& ) = delete;

	void SetMemberFunctionDataset( const std::vector<SMemberFunctionHeaderDataset>& oMemberFunctionDatasetVector );
	const std::vector<SMemberFunctionHeaderDataset>& GetMemberFunctionDataset() const;

	std::filesystem::path GetPath() const;

	const std::string& GetContent() const;
	std::vector<std::string> GetCodeLines() const;

	EType GetType() const;

private:
	std::filesystem::path m_oPath;
	std::string m_oContentString;

	EType m_eType;

	std::vector<SMemberFunctionHeaderDataset> m_oMemberFunctionDatasetVector;
};
