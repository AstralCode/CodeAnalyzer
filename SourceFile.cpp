#include "SourceFile.h"

// ^^x
// CSourceFile::CSourceFile
// 3BGO JIRA-238 24-09-2020
CSourceFile::CSourceFile( const std::filesystem::path& oPath ) :
	CCodeFile{ oPath }
{

}

// ^^x
// void CSourceFile::SetMemberFunctions
// 3BGO JIRA-238 24-09-2020
void CSourceFile::SetMemberFunctions( std::vector<SFindDataResult<CFunction>>&& oMemberFunctionDatasetVector )
{
	m_oMemberFunctionDatasetVector = std::move( oMemberFunctionDatasetVector );
}


// ^^x
// const std::vector<SFindDataResult<CFunction>>& CSourceFile::GetMemberFunctions
// 3BGO JIRA-238 24-09-2020
const std::vector<SFindDataResult<CFunction>>& CSourceFile::GetMemberFunctions() const
{
	return m_oMemberFunctionDatasetVector;
}
