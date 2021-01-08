#pragma once

#include <fstream>
#include <filesystem>

#include "FindDataResult.h"
#include "Function.h"

class CCodeAnalyzerLogger final
{
public:
	CCodeAnalyzerLogger( const std::filesystem::path& oDirectoryPath );

	void Open( const std::string& oFilenameString );
	void Remove();

	void Write( const std::string& oMessageString );
	void WriteLine( const std::string& oMessageString = {} );

	void Log( const SFindDataResult<CVariable>& oVariable, bool bIsMember = false );
	void Log( const SFindDataResult<CFunction>& oFunction );

private:
	std::ofstream m_oFileStream;
	std::filesystem::path m_oDirectoryPath;
	std::filesystem::path m_oFilenamePath;
};
