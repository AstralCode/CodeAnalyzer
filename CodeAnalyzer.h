#pragma once

#include <memory>

#include "ProgramStatusCodes.h"
#include "CommandLineArgumentDataset.h"
#include "StatisticsAnalyzerModule.h"
#include "CodeParser.h"
#include "CodeFileTypes.h"

class CCodeAnalyzer final
{
public:
	using StatisticsAnalyzerModule = std::reference_wrapper<CStatisticsAnalyzerModule>;
	using ConstStatisticsAnalyzerModule = std::reference_wrapper<const CStatisticsAnalyzerModule>;

	using StatisticsAnalyzerModuleVector = std::vector<StatisticsAnalyzerModule>;
	using ConstStatisticsAnalyzerModuleVector = std::vector<ConstStatisticsAnalyzerModule>;

	CCodeAnalyzer() = default;

	CCodeAnalyzer( const CCodeAnalyzer& ) = delete;
	CCodeAnalyzer& operator=( const CCodeAnalyzer& ) = delete;

	template<typename TDerivedStatisticsAnalyzerModule, typename... TArguments>
	void AddAnalyzerModule( TArguments&&... oArguments );

	ConstStatisticsAnalyzerModuleVector GetAnalyzerModules() const;

	EProgramStatusCodes Execute( const SCommandLineArgumentDataset& oCommandLineArgumentDataset );

private:
	static ECodeFileType CheckFileType( const std::filesystem::path& oFilePath );

	EProgramStatusCodes ReadFileContent( const std::filesystem::path& oFilePath, std::string& oFileContentString ) const;
	void PreProcessFileContent( std::string& oFileContentString ) const;

	void ProcessHeaderFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString );
	void ProcessSourceFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString );

	unsigned int CountNumberCodeFiles( const std::filesystem::path& oDirectoryPath ) const;
	std::uintmax_t CountSizeCodeFiles( const std::filesystem::path& oDirectoryPath ) const;

	void PrintProgress( const unsigned int uiFileNumber, const unsigned int uiFileCount ) const;

	bool IsCodeFile( const std::filesystem::path& oFilePath ) const;

	CCodeParser m_oCodePareser;
	std::filesystem::path m_oInputDirectoryPath;
	std::vector<std::unique_ptr<CStatisticsAnalyzerModule>> m_oAnalyzerModuleVector;
};

// ^^x
// void CCodeAnalyzer::AddAnalyzerModule
// 3BGO JIRA-238 24-09-2020
template<typename TDerivedStatisticsAnalyzerModule, typename... TArguments>
inline void CCodeAnalyzer::AddAnalyzerModule( TArguments&&... oArguments )
{
	static_assert(std::is_base_of<CStatisticsAnalyzerModule, TDerivedStatisticsAnalyzerModule>::value, "TDerivedStatisticsAnalyzerModule class must derived from CStatisticsAnalyzerModule base class");

	m_oAnalyzerModuleVector.push_back(std::make_unique<TDerivedStatisticsAnalyzerModule>( std::forward<TArguments&&>( oArguments )... ) );
}
