#pragma once

#include <filesystem>
#include <vector>

class CCodeFile
{
public:
	enum class EType
	{
		eUnknown,
		eHeader,
		eSource
	};

	CCodeFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString );
	virtual ~CCodeFile() = default;

	static EType CheckFileExtension( const std::filesystem::path& oFilePath );

	std::vector<std::string> GetCodeLines() const;
	const std::string& GetContent() const;

	std::filesystem::path GetPath() const;

	unsigned int GetLineCount() const;

private:
	std::filesystem::path m_oFilePath;
	std::string m_oFileContentString;
};

