#pragma once

#include <vector>
#include <filesystem>

class CCommandLineHandler final
{
public:
	CCommandLineHandler( int iArgumentCount, char* apcArguments[] );

	int HandleArguments( std::filesystem::path& oInputDirectoryPath,
						 std::filesystem::path& oOutputDirectoryPath ) const;

	void PrintUsage() const;

private:
	std::vector<std::string> m_aArgumentStrings;
};
