#pragma once

#include "CodeFile.h"
#include "CodeFunctionDataset.h"

class CSourceCodeFile final : public CCodeFile
{
public:
	CSourceCodeFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString );

	std::vector<std::pair<std::string, CCodeFunctionDataset>> RetrieveCodeFunctionDataset() const;
};
