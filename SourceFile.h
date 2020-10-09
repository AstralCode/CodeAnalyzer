#pragma once

#include <vector>

#include "CodeFile.h"
#include "Function.h"
#include "FindDataResult.h"

class CSourceFile final : public CCodeFile
{
public:
	CSourceFile( const std::filesystem::path& oPath );

	void SetMemberFunctions( std::vector<SFindDataResult<CFunction>>&& oMemberFunctionDatasetVector );
	const std::vector<SFindDataResult<CFunction>>& GetMemberFunctions() const;

private:
	std::vector<SFindDataResult<CFunction>> m_oMemberFunctionDatasetVector;
};
