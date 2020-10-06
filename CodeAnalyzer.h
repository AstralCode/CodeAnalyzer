#pragma once

#include <memory>

#include "ProgramStatusCodes.h"
#include "CommandLineArgumentDataset.h"
#include "StatisticsAnalyzerModule.h"
#include "CodeParser.h"

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

	template<typename TDerivedStatisticsAnalyzerModule>
	void AddModule();

	ConstStatisticsAnalyzerModuleVector GetModules() const;

	EProgramStatusCodes Execute( const SCommandLineArgumentDataset& oCommandLineArgumentDataset );

private:
	static CCodeFile::EType AnalyzeFileType( const std::filesystem::path& oFilePath );

	void ProcessCodeFile( CStatisticsAnalyzerModule& oAnalyzerModule, const CCodeFile& oCodeFile ) const;
	EProgramStatusCodes ReadFileContent( const std::filesystem::path& oFilePath, std::string& oFileContentString ) const;
	void PreProcessFileContent( std::string& oFileContentString ) const;

	unsigned int CountNumberCodeFiles( const std::filesystem::path& oDirectoryPath ) const;
	std::uintmax_t CountSizeCodeFiles( const std::filesystem::path& oDirectoryPath ) const;

	void PrintProgress( const unsigned int uiFileNumber, const unsigned int uiFileCount ) const;

	bool IsCodeFile( const std::filesystem::path& oFilePath ) const;

	CCodeParser m_oCodePareser;
	std::filesystem::path m_oInputDirectoryPath;
	std::vector<std::unique_ptr<CStatisticsAnalyzerModule>> m_oStatisticsAnalyzerModuleVector;
};

template<typename TDerivedStatisticsAnalyzerModule>
inline void CCodeAnalyzer::AddModule()
{
	static_assert(std::is_base_of<CStatisticsAnalyzerModule, TDerivedStatisticsAnalyzerModule>::value, "TDerivedStatisticsAnalyzerModule class must derived from CStatisticsAnalyzerModule base class");

	m_oStatisticsAnalyzerModuleVector.push_back(std::make_unique<TDerivedStatisticsAnalyzerModule>( m_oCodePareser ));
}
