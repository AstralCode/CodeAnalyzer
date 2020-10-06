#include "CodeFile.h"

// ^^x
// CCodeFile::CCodeFile
// 3BGO JIRA-238 24-09-2020
CCodeFile::CCodeFile( const std::filesystem::path& oPath ) :
	m_oPath{ oPath },
	m_uiCodeLineCount{ 0u }
{

}

// ^^x
// std::filesystem::path CCodeFile::GetPath
// 3BGO JIRA-238 24-09-2020
std::filesystem::path CCodeFile::GetPath() const
{
	return m_oPath;
}

// ^^x
// void CCodeFile::SetCodeLineCount
// 3BGO JIRA-238 05-10-2020
void CCodeFile::SetCodeLineCount( const unsigned int uiCount )
{
	m_uiCodeLineCount = uiCount;
}

// ^^x
// unsigned int CCodeFile::GetCodeLineCount
// 3BGO JIRA-238 05-10-2020
unsigned int CCodeFile::GetCodeLineCount() const
{
	return m_uiCodeLineCount;
}
