#include "HeaderCodeFile.h"

// ^^x
// CHeaderCodeFile::CHeaderCodeFile
// 3BGO JIRA-238 24-09-2020
CHeaderCodeFile::CHeaderCodeFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString ) :
	CCodeFile{ oFilePath, oFileContentString }
{

}
