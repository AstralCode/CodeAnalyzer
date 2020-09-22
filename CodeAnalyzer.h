#pragma once

#include <vector>
#include <memory>
#include <filesystem>

#include "StatisticsAnalyzerModule.h"

class CCodeAnalyzer final
{
public:
	CCodeAnalyzer( const std::filesystem::path& oInputDirectoryPath );

	template<typename TDerivedModule>
	void AddModule();

	std::vector<std::reference_wrapper<const CStatisticsAnalyzerModule>> GetModules() const;

	int Execute();

private:
	std::filesystem::path m_oInputDirectoryPath;

	std::vector<std::unique_ptr<CStatisticsAnalyzerModule>> m_aStatisticsAnalyzerModules;
};

template<typename TDerivedModule>
inline void CCodeAnalyzer::AddModule()
{
	static_assert(std::is_base_of<CStatisticsAnalyzerModule, TDerivedModule>::value, "TDerivedModule must derived from CStatisticsAnalyzerModule");

	m_aStatisticsAnalyzerModules.push_back(std::make_unique<TDerivedModule>());
}
