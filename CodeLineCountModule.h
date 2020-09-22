#pragma once

#include "StatisticsAnalyzerModule.h"

class CCodeLineCountModule final : public CStatisticsAnalyzerModule
{
public:
	CCodeLineCountModule();

	int ProcessLine( const std::string& oLine ) override;

	void OnStartProcess( const std::filesystem::path& oFilePath ) override;
	void OnEndProcess( const std::filesystem::path& oFilePath ) override;

	std::string GetStatisticsHeader() const override;
	unsigned int GetStatisticsResult() const override;

	bool HasAcceptFileExtension( const std::filesystem::path& oFileExtensionPath ) const override;

private:
	unsigned int m_uiStatisticsResult;
};
