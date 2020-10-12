#pragma once

#include <vector>

#include "ProgramStatusCodes.h"
#include "CommandLineArgumentDataset.h"

class CCommandLineHandler final
{
public:
	CCommandLineHandler( int iArgumentCount, char* apcArguments[] );

	CCommandLineHandler( const CCommandLineHandler& ) = delete;
	CCommandLineHandler& operator=( const CCommandLineHandler& ) = delete;

	EProgramStatusCodes HandleArguments( SCommandLineArgumentDataset& oArgumentDataset ) const;

	std::string GetUsageMessage() const;

private:
	EProgramStatusCodes HandleRequiredArguments( SCommandLineArgumentDataset& oArgumentDataset ) const;
	EProgramStatusCodes HandleOptionalArguments( SCommandLineArgumentDataset& oArgumentDataset ) const;

	EProgramStatusCodes HandleOptionalArgument( SCommandLineArgumentDataset& oArgumentDataset, const std::string& oOptionString, const std::string& oArgumentString ) const;

	void AssignOptionalArgument( std::optional<std::string>& oOutputString, const std::string& oArgumentString ) const;

	std::vector<std::string> m_oArgumentVector;
};
