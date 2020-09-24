#pragma once

#include <vector>
#include <filesystem>

#include "ProgramStatusCodes.h"

class CCommandLineHandler final
{
public:
	CCommandLineHandler( int iArgumentCount, char* apcArguments[] );

	EProgramStatusCodes HandleArguments( std::filesystem::path& oInputDirectoryPath, std::filesystem::path& oOutputDirectoryPath ) const;

	std::string GetUsageMessage() const;

private:
	std::vector<std::string> m_oArgumentVector;
};
