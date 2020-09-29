#pragma once

#include "CodeFile.h"
#include "CodeMemberFunctionDataset.h"

class CSourceCodeFile final : public CCodeFile
{
public:
	CSourceCodeFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString );

	std::vector<std::pair<std::string, CCodeMemberFunctionDataset>> RetrieveMemberFunctionDataset() const;
};
