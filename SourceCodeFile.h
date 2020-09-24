#pragma once

#include "CodeFile.h"

class CSourceCodeFile final : public CCodeFile
{
public:
	CSourceCodeFile( const std::filesystem::path& oFilePath, const CodeLineVector& oCodeLineVector );
};
