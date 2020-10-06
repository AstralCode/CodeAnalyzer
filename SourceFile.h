#pragma once

#include <vector>

#include "CodeFile.h"
#include "MemberFunctionDataset.h"

class CSourceFile final : public CCodeFile
{
public:
	CSourceFile( const std::filesystem::path& oPath );

	void SetMemberFunctionDataset( std::vector<SMemberFunctionDataset>&& oMemberFunctionDatasetVector );
	const std::vector<SMemberFunctionDataset>& GetMemberFunctions() const;

private:
	std::vector<SMemberFunctionDataset> m_oMemberFunctionDatasetVector;
};
