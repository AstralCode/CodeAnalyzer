#pragma once

#include <filesystem>

#include "ProgramStatusCodes.h"

class CStatisticsAnalyzerModule
{
public:
	CStatisticsAnalyzerModule() = default;
	virtual ~CStatisticsAnalyzerModule() = default;

	virtual int ProcessLine( const std::string& oLine ) = 0;

	virtual void OnStartProcess( const std::filesystem::path& oFilePath ) = 0;
	virtual void OnEndProcess( const std::filesystem::path& oFilePath ) = 0;

	virtual std::string GetStatisticsHeader() const = 0;
	virtual unsigned int GetStatisticsResult() const = 0;

	virtual bool HasAcceptFileExtension( const std::filesystem::path& oFileExtensionPath ) const = 0;
};