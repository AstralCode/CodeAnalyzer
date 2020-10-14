#pragma once

#include <map>
#include <vector>

#include "CodeFile.h"
#include "Function.h"

class CSourceFile final : public CCodeFile
{
public:
	CSourceFile( const std::filesystem::path& oPath );

	void SetGlobalVariables( std::vector<SFindDataResult<CVariable>>&& oGlobalVariableVector );
	const std::vector<SFindDataResult<CVariable>>& GetGlobalVariables() const;

	void SetGlobalFunctions( std::vector<SFindDataResult<CFunction>>&& oGlobalFunctionVector );
	const std::vector<SFindDataResult<CFunction>>& GetGlobalFunctions() const;

	void SetMemberVariables( std::map<std::string, SFindDataResult<CVariable>>&& oMemberVariableMap );
	const std::map<std::string, SFindDataResult<CVariable>>& GetMemberVariables() const;

	void SetMemberFunctions( std::vector<SFindDataResult<CFunction>>&& oMemberFunctionVector );
	const std::vector<SFindDataResult<CFunction>>& GetMemberFunctions() const;

private:
	std::vector<SFindDataResult<CVariable>> m_oGlobalVariableVector;
	std::vector<SFindDataResult<CFunction>> m_oGlobalFunctionVector;

	std::map<std::string, SFindDataResult<CVariable>> m_oMemberVariableMap;
	std::vector<SFindDataResult<CFunction>> m_oMemberFunctionVector;
};
