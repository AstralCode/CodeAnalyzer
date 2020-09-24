#pragma once

#include <vector>
#include <memory>
#include <filesystem>

#include "ProgramStatusCodes.h"
#include "StatisticsAnalyzerModule.h"
#include "CodeFile.h"

class CCodeAnalyzer final
{
public:
	using StatisticsAnalyzerModule = std::reference_wrapper<CStatisticsAnalyzerModule>;
	using ConstStatisticsAnalyzerModule = std::reference_wrapper<const CStatisticsAnalyzerModule>;

	using StatisticsAnalyzerModuleVector = std::vector<StatisticsAnalyzerModule>;
	using ConstStatisticsAnalyzerModuleVector = std::vector<ConstStatisticsAnalyzerModule>;

	template<typename TDerivedStatisticsAnalyzerModule>
	void AddModule();

	ConstStatisticsAnalyzerModuleVector GetModules() const;

	EProgramStatusCodes Execute( const std::filesystem::path& oInputDirectoryPath );

private:
	EProgramStatusCodes ReadCodeFileContent( const std::filesystem::path& oFilePath, CCodeFile::CodeLineVector& oCodeLineVector ) const;
	void ProcessCodeFile( const std::filesystem::path& oFilePath, const CCodeFile::CodeLineVector& oCodeLineVector, const CCodeFile::EType oFileCodeType );

	std::filesystem::path m_oInputDirectoryPath;

	std::vector<std::unique_ptr<CStatisticsAnalyzerModule>> m_oStatisticsAnalyzerModuleVector;
};

template<typename TDerivedStatisticsAnalyzerModule>
inline void CCodeAnalyzer::AddModule()
{
	static_assert(std::is_base_of<CStatisticsAnalyzerModule, TDerivedStatisticsAnalyzerModule>::value, "TDerivedStatisticsAnalyzerModule class must derived from CStatisticsAnalyzerModule base class");

	m_oStatisticsAnalyzerModuleVector.push_back(std::make_unique<TDerivedStatisticsAnalyzerModule>());
}
