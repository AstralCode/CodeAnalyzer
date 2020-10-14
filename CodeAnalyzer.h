#pragma once

#include <memory>
#include <filesystem>

#include "ProgramStatusCodes.h"
#include "CodeAnalyzerModule.h"
#include "CodeParser.h"
#include "CodeFileTypes.h"

class CCodeAnalyzer final
{
public:
	CCodeAnalyzer() = default;

	CCodeAnalyzer( const CCodeAnalyzer& ) = delete;
	CCodeAnalyzer& operator=( const CCodeAnalyzer& ) = delete;

	template<typename TDerivedCodeAnalyzerModule, typename... TArguments>
	void AddAnalyzerModule( TArguments&&... oArguments );

	std::vector<SStatisticsResult> GetStatisticsResults() const;

	EProgramStatusCodes Execute( const std::filesystem::path& oInputDirectoryPath );

	static unsigned int CountNumberCodeFiles( const std::filesystem::path& oDirectoryPath );
	static std::uintmax_t CountSizeCodeFiles( const std::filesystem::path& oDirectoryPath );

	static ECodeFileType CheckFileType( const std::filesystem::path& oFilePath );
	static bool IsCodeFile( const std::filesystem::path& oFilePath );

private:
	EProgramStatusCodes ReadFileContent( const std::filesystem::path& oFilePath, std::string& oFileContentString ) const;
	void PreProcessFileContent( std::string& oFileContentString ) const;

	void ProcessHeaderFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString );
	void ProcessSourceFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString );

	void PrintProgress( const unsigned int uiFileNumber, const unsigned int uiFileCount ) const;

	CCodeParser m_oCodePareser;
	std::filesystem::path m_oInputDirectoryPath;
	std::vector<std::unique_ptr<CCodeAnalyzerModule>> m_oAnalyzerModuleVector;
};

// ^^x
// void CCodeAnalyzer::AddAnalyzerModule
// 3BGO JIRA-238 24-09-2020
template<typename TDerivedCodeAnalyzerModule, typename... TArguments>
inline void CCodeAnalyzer::AddAnalyzerModule( TArguments&&... oArguments )
{
	static_assert(std::is_base_of<CCodeAnalyzerModule, TDerivedCodeAnalyzerModule>::value, "TDerivedCodeAnalyzerModule class must derived from CCodeAnalyzerModule base class");

	m_oAnalyzerModuleVector.push_back(std::make_unique<TDerivedCodeAnalyzerModule>( std::forward<TArguments&&>( oArguments )... ) );
}
