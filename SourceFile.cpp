#include "SourceFile.h"

// ^^x
// CSourceFile::CSourceFile
// 3BGO JIRA-238 24-09-2020
CSourceFile::CSourceFile( const std::filesystem::path& oPath ) :
	CCodeFile{ oPath }
{

}

// ^^x
// void CSourceFile::SetGlobalVariables
// 3BGO JIRA-238 12-10-2020
void CSourceFile::SetGlobalVariables( std::vector<SFindDataResult<CVariable>>&& oGlobalVariableVector )
{
	m_oGlobalVariableVector = std::move( oGlobalVariableVector );
}

// ^^x
// const std::vector<SFindDataResult<CVariable>>& CSourceFile::GetGlobalVariables
// 3BGO JIRA-238 12-10-2020
const std::vector<SFindDataResult<CVariable>>& CSourceFile::GetGlobalVariables() const
{
	return m_oGlobalVariableVector;
}

// ^^x
// void CSourceFile::SetGlobalFunctions
// 3BGO JIRA-238 24-09-2020
void CSourceFile::SetGlobalFunctions( std::vector<SFindDataResult<CFunction>>&& oGlobalFunctionVector )
{
	m_oGlobalFunctionVector = std::move( oGlobalFunctionVector );
}


// ^^x
// const std::vector<SFindDataResult<CFunction>>& CSourceFile::GetGlobalFunctions
// 3BGO JIRA-238 24-09-2020
const std::vector<SFindDataResult<CFunction>>& CSourceFile::GetGlobalFunctions() const
{
	return m_oGlobalFunctionVector;
}

// ^^x
// void CSourceFile::SetMemberFunctions
// 3BGO JIRA-238 24-09-2020
void CSourceFile::SetMemberFunctions( std::vector<SFindDataResult<CFunction>>&& oMemberFunctionVector )
{
	m_oMemberFunctionVector = std::move( oMemberFunctionVector );
}


// ^^x
// const std::vector<SFindDataResult<CFunction>>& CSourceFile::GetMemberFunctions
// 3BGO JIRA-238 24-09-2020
const std::vector<SFindDataResult<CFunction>>& CSourceFile::GetMemberFunctions() const
{
	return m_oMemberFunctionVector;
}
