#include "CodeFile.h"

#include <sstream>

// ^^x
// CCodeFile::CCodeFile
// 3BGO JIRA-238 24-09-2020
CCodeFile::CCodeFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString ) :
	m_oFilePath{ oFilePath },
	m_oFileContentString{ oFileContentString }
{

}

// ^^x
// CCodeFile::EType CCodeFile::CheckFileExtension
// 3BGO JIRA-238 24-09-2020
CCodeFile::EType CCodeFile::CheckFileExtension( const std::filesystem::path& oFilePath )
{
	CCodeFile::EType eFileType = CCodeFile::EType::eUnknown;

	if ( oFilePath.has_extension() )
	{
		if ( oFilePath.extension() == ".h" )
		{
			eFileType = CCodeFile::EType::eHeader;
		}

		if ( oFilePath.extension() == ".cpp" )
		{
			eFileType = CCodeFile::EType::eSource;
		}
	}

	return eFileType;
}

// ^^x
// std::vector<std::string> CCodeFile::GetCodeLines
// 3BGO JIRA-238 24-09-2020
std::vector<std::string> CCodeFile::GetCodeLines() const
{
	std::vector<std::string> oCodeLineVector{};

	std::istringstream oStringStream{ m_oFileContentString };
	std::string oCodeLine{};

	while ( std::getline( oStringStream, oCodeLine ) )
	{
		oCodeLineVector.push_back( oCodeLine );
	}

	return oCodeLineVector;
}

// ^^x
// const std::string& CCodeFile::GetContent
// 3BGO JIRA-238 24-09-2020
const std::string& CCodeFile::GetContent() const
{
	return m_oFileContentString;
}

// ^^x
// std::filesystem::path CCodeFile::GetPath
// 3BGO JIRA-238 24-09-2020
std::filesystem::path CCodeFile::GetPath() const
{
	return m_oFilePath;
}

// ^^x
// unsigned int CCodeFile::GetLineCount
// 3BGO JIRA-238 24-09-2020
unsigned int CCodeFile::GetLineCount() const
{
	return GetCodeLines().size();
}
