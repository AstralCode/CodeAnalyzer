#pragma once

#include "CodeFile.h"

class CHeaderCodeFile final : public CCodeFile
{
public:
	CHeaderCodeFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString );
};
