#pragma once

#include <vector>
#include <memory>
#include <filesystem>

#include "StatisticsAnalyzerModule.h"

class CCodeAnalyzer final
{
public:
	using StatisticsAnalyzerModule = std::reference_wrapper<CStatisticsAnalyzerModule>;
	using ConstStatisticsAnalyzerModule = std::reference_wrapper<const CStatisticsAnalyzerModule>;

	using StatisticsAnalyzerModuleVector = std::vector<StatisticsAnalyzerModule>;
	using ConstStatisticsAnalyzerModuleVector = std::vector<ConstStatisticsAnalyzerModule>;

	CCodeAnalyzer( const std::filesystem::path& oInputDirectoryPath );

	template<typename TDerivedModule>
	void AddModule();

	ConstStatisticsAnalyzerModuleVector GetModules() const;

	int Execute() const;

private:
	StatisticsAnalyzerModuleVector GetModules( const std::filesystem::path& oAcceptedFileExtensionPath ) const;

	std::filesystem::path m_oInputDirectoryPath;

	std::vector<std::unique_ptr<CStatisticsAnalyzerModule>> m_aStatisticsAnalyzerModules;
};

template<typename TDerivedStatisticsAnalyzerModule>
inline void CCodeAnalyzer::AddModule()
{
	static_assert(std::is_base_of<CStatisticsAnalyzerModule, TDerivedStatisticsAnalyzerModule>::value, "TDerivedStatisticsAnalyzerModule class must derived from CStatisticsAnalyzerModule base class");

	m_aStatisticsAnalyzerModules.push_back(std::make_unique<TDerivedStatisticsAnalyzerModule>());
}
