#pragma once

#include <filesystem>
#include <vector>

class CCodeFile
{
public:
	using CodeLineVector = std::vector<std::string>;

	enum class EType
	{
		eUnknown,
		eHeader,
		eSource
	};

	CCodeFile( const std::filesystem::path& oFilePath, const CodeLineVector& oCodeLineVector );
	virtual ~CCodeFile() = default;

	static EType CheckFileExtension( const std::filesystem::path& oFilePath );

	const CodeLineVector& GetCodeLines() const;
	std::string GetCode() const;

	std::filesystem::path GetPath() const;

	unsigned int GetLineCount() const;

private:
	std::filesystem::path m_oFilePath;
	CodeLineVector m_oCodeLineVector;
};

