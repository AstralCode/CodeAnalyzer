#pragma once

#include <memory>
#include <filesystem>
#include <optional>

#include "ProgramStatusCodes.h"
#include "CodeParser.h"
#include "CodeAnalyzerModule.h"
#include "StatisticsCollection.h"
#include "CodeFileTypes.h"

class CCodeAnalyzer final
{
public:
	CCodeAnalyzer() = default;

	CCodeAnalyzer( const CCodeAnalyzer& ) = delete;
	CCodeAnalyzer& operator=( const CCodeAnalyzer& ) = delete;

	template<typename TDerivedCodeAnalyzerModule, typename... TArguments>
	void AddAnalyzerModule( TArguments&&... oArguments );

	const CStatisticsCollection& GetStatisticsCollection() const;

	EProgramStatusCodes Execute( const std::filesystem::path& oInputDirectoryPath, std::optional<std::string> oDeveloperString = {} );

private:
	EProgramStatusCodes ReadFileContent( const std::filesystem::path& oFilePath, std::string& oFileContentString ) const;
	EProgramStatusCodes ProcessCodeFile( const ECodeFileTypes eFileType, const std::filesystem::path& oFilePath, std::optional<std::string> oDeveloperString );

	void PreProcessHeaderFileContent( std::string& oFileContentString ) const;
	void PreProcessSourceFileContent( std::string& oFileContentString ) const;

	void ProcessHeaderFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString, std::optional<std::string> oDeveloperString );
	void ProcessSourceFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString, std::optional<std::string> oDeveloperString );

	void FilterResults( std::vector<SFindDataResult<CFunction>>& oFunctionVector, std::optional<std::string> oDeveloperString ) const;

	void OnPreExecute( const std::filesystem::path& oInputDirectoryPath, std::size_t& uiCodeFileCount );
	void OnPostExecute( const EProgramStatusCodes eStatus );

	std::size_t CountNumberCodeFiles( const std::filesystem::path& oDirectoryPath ) const;
	std::size_t CountNumberCodeFiles( const std::filesystem::path& oDirectoryPath, const ECodeFileTypes eCodeFileType ) const;
	std::uintmax_t CountSizeCodeFiles( const std::filesystem::path& oDirectoryPath ) const;

	ECodeFileTypes CheckFileType( const std::filesystem::path& oFilePath ) const;
	bool IsCodeFile( const std::filesystem::path& oFilePath ) const;

	void PrintProgress( const std::size_t uiFileNumber, const std::size_t uiFileCount ) const;

	std::filesystem::path m_oInputDirectoryPath;

	CCodeParser m_oCodePareser;
	CStatisticsCollection m_oStatisticsCollection;
	
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
