#pragma once

#include <string>
#include <vector>

#include "StatisticsCollection.h"
#include "CodeAnalyzerLogger.h"

class CHeaderFile;
class CSourceFile;
class CStatisticsCollection;

class CCodeAnalyzerModule
{
public:
	CCodeAnalyzerModule( const std::filesystem::path& oLoggerDirectoryPath, const bool bLoggingEnabled = false );
	virtual ~CCodeAnalyzerModule() = default;

	CCodeAnalyzerModule( const CCodeAnalyzerModule& ) = delete;
	CCodeAnalyzerModule& operator=( const CCodeAnalyzerModule& ) = delete;

	virtual void OnPreExecute() = 0;

	virtual void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) = 0;
	virtual void ProcessSourceFile( const CSourceFile& oSourceFile ) = 0;

	virtual void OnPostExecute( CStatisticsCollection& oFinalStatisticsCollection ) = 0;

	virtual void OnCollectedStatistics( CStatisticsCollection& oFinalStatisticsCollection ) = 0;

	bool IsLoggingEnabled() const;

protected:
	CStatisticsCollection m_oStatisticsCollection;
	mutable CCodeAnalyzerLogger m_oLogger;

private:
	bool m_bLoggingEnabled;
};
