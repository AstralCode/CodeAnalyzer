#pragma once

#include <vector>

#include "CodeFile.h"
#include "Function.h"

class CHeaderFile final : public CCodeFile
{
public:
	CHeaderFile( const std::filesystem::path& oPath );

	void SetMemberVariables( std::vector<SFindDataResult<CVariable>>&& oMemberVariableVector );
	const std::vector<SFindDataResult<CVariable>>& GetMemberVariables() const;

private:
	std::vector<SFindDataResult<CVariable>> m_oMemberVariableVector;
};
