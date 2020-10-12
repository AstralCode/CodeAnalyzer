#pragma once

#include <vector>

#include "CodeFile.h"
#include "Function.h"
#include "FindDataResult.h"

class CSourceFile final : public CCodeFile
{
public:
	CSourceFile( const std::filesystem::path& oPath );

	void SetGlobalFunctions( std::vector<SFindDataResult<CFunction>>&& oGlobalFunctionVector );
	const std::vector<SFindDataResult<CFunction>>& GetGlobalFunctions() const;

	void SetMemberFunctions( std::vector<SFindDataResult<CFunction>>&& oMemberFunctionVector );
	const std::vector<SFindDataResult<CFunction>>& GetMemberFunctions() const;

private:
	std::vector<SFindDataResult<CFunction>> m_oGlobalFunctionVector;
	std::vector<SFindDataResult<CFunction>> m_oMemberFunctionVector;
};
