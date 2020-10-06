#pragma once

#include <filesystem>

class CCodeFile
{
public:
	CCodeFile( const std::filesystem::path& oPath );
	virtual ~CCodeFile() = default;

	CCodeFile( const CCodeFile& ) = delete;
	CCodeFile& operator=( const CCodeFile& ) = delete;

	std::filesystem::path GetPath() const;

	void SetCodeLineCount( const unsigned int uiCount );
	unsigned int GetCodeLineCount() const;

private:
	std::filesystem::path m_oPath;
	unsigned int m_uiCodeLineCount;
};
