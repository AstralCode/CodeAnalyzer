#include "CodeFile.h"

// ^^x
// CCodeFile::CCodeFile
// 3BGO JIRA-238 24-09-2020
CCodeFile::CCodeFile( const std::filesystem::path& oFilePath, const CodeLineVector& oCodeLineVector ) :
	m_oFilePath{ oFilePath },
	m_oCodeLineVector{ oCodeLineVector }
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
// const CCodeFile::CodeLineVector& CCodeFile::GetCodeLines
// 3BGO JIRA-238 24-09-2020
const CCodeFile::CodeLineVector& CCodeFile::GetCodeLines() const
{
	return m_oCodeLineVector;
}

// ^^x
// std::string CCodeFile::GetCode
// 3BGO JIRA-238 24-09-2020
std::string CCodeFile::GetCode() const
{
	std::string oCodeString{};

	for ( const std::string& oCodeLineString : m_oCodeLineVector )
	{
		oCodeString.append( oCodeLineString );
	}

	return oCodeString;
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
	return m_oCodeLineVector.size();
}
