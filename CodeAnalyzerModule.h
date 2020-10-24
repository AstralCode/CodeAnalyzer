#pragma once

#include <string>
#include <vector>

class CHeaderFile;
class CSourceFile;
class CStatisticsCollection;

class CCodeAnalyzerModule
{
public:
	CCodeAnalyzerModule() = default;
	virtual ~CCodeAnalyzerModule() = default;

	CCodeAnalyzerModule( const CCodeAnalyzerModule& ) = delete;
	CCodeAnalyzerModule& operator=( const CCodeAnalyzerModule& ) = delete;

	virtual void OnPreExecute( CStatisticsCollection& oStatisticsCollection ) = 0;

	virtual void ProcessHeaderFile( const CHeaderFile& oHeaderFile, CStatisticsCollection& oStatisticsCollection ) = 0;
	virtual void ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection ) = 0;

	virtual void OnPostExecute( CStatisticsCollection& oStatisticsCollection ) = 0;
};
