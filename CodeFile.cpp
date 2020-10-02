#include "CodeFile.h"

#include "StringHelper.h"

// ^^x
// CCodeFile::CCodeFile
// 3BGO JIRA-238 24-09-2020
CCodeFile::CCodeFile( const std::filesystem::path& oPath, const std::string& oContentString, const EType eType ) :
	m_oPath{ oPath },
	m_oContentString{ oContentString },
	m_eType{ eType }
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
// const std::string& CCodeFile::GetContent
// 3BGO JIRA-238 24-09-2020
const std::string& CCodeFile::GetContent() const
{
	return m_oContentString;
}

// ^^x
// std::vector<std::string> CCodeFile::GetCodeLines
// 3BGO JIRA-238 24-09-2020
std::vector<std::string> CCodeFile::GetCodeLines() const
{
	return CStringHelper::SplitLines( m_oContentString );
}

// ^^x
// CCodeFile::EType CCodeFile::GetType
// 3BGO JIRA-238 24-09-2020
CCodeFile::EType CCodeFile::GetType() const
{
	return m_eType;
}
