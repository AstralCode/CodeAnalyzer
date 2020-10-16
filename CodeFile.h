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

	void SetCodeLineCount( const std::size_t uiCount );
	std::size_t GetCodeLineCount() const;

private:
	std::filesystem::path m_oPath;
	std::size_t m_uiCodeLineCount;
};
