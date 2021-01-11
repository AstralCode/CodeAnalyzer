#pragma once

#include <set>

#include "CodeAnalyzerModule.h"
#include "Function.h"

/*
	### Description ###
	This module calculates the total number of functions that
	have more than 5 arguments on the list
*/
class CFunctionArgsCountModule final : public CCodeAnalyzerModule
{
public:
	using CCodeAnalyzerModule::CCodeAnalyzerModule;

	void OnPreExecute() override;

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile ) override;

	void OnPostExecute( CStatisticsCollection& oFinalStatisticsCollection ) override;

	void OnCollectedStatistics( CStatisticsCollection& oFinalStatisticsCollection ) override;

private:
	void CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector );

	std::set<SFindDataResult<CFunction>> m_oFunctionSet;
};
