#pragma once

#include "CodeFile.h"

class CHeaderFile final : public CCodeFile
{
public:
	CHeaderFile( const std::filesystem::path& oPath );
};
