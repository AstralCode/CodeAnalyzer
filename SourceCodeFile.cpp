#include "SourceCodeFile.h"

// ^^x
// CSourceCodeFile::CSourceCodeFile
// 3BGO JIRA-238 24-09-2020
CSourceCodeFile::CSourceCodeFile( const std::filesystem::path& oFilePath, const CodeLineVector& oCodeLineVector ) :
	CCodeFile{ oFilePath, oCodeLineVector }
{

}
