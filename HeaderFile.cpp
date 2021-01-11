#include "HeaderFile.h"

// ^^x
// CHeaderFile::CHeaderFile
// 3BGO NTP-1 24-09-2020
CHeaderFile::CHeaderFile( const std::filesystem::path& oPath ) :
	CCodeFile{ oPath }
{

}

// ^^x
// const std::vector<SFindDataResult<CVariable>>& CSourceFile::SetMemberVariables
// 3BGO NTP-1 08-01-2021
void CHeaderFile::SetMemberVariables( std::vector<SFindDataResult<CVariable>>&& oMemberVariableVector )
{
	m_oMemberVariableVector = std::move( oMemberVariableVector );
}

// ^^x
// const std::vector<SFindDataResult<CVariable>>& CSourceFile::GetMemberVariables
// 3BGO NTP-1 08-01-2021
const std::vector<SFindDataResult<CVariable>>& CHeaderFile::GetMemberVariables() const
{
	return m_oMemberVariableVector;
}
