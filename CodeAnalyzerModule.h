#pragma once

#include <string>
#include <vector>

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

	virtual void OnPreExecute( CStatisticsCollection& oStatisticsCollection ) = 0;

	virtual void ProcessHeaderFile( const CHeaderFile& oHeaderFile, CStatisticsCollection& oStatisticsCollection ) = 0;
	virtual void ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection ) = 0;

	virtual void OnPostExecute( CStatisticsCollection& oStatisticsCollection ) = 0;

	bool IsLoggingEnabled() const;

protected:
	mutable CCodeAnalyzerLogger m_oLogger;

private:
	bool m_bLoggingEnabled;
};
