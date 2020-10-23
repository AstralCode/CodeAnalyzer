#pragma once

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
	void OnExcute( CStatisticsCollection& oStatisticsCollection ) override;

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile, CStatisticsCollection& oStatisticsCollection ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection ) override;

	void OnExcuteComplete( CStatisticsCollection& oStatisticsCollection ) override;

private:
	void CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector, CStatisticsCollection& oStatisticsCollection );
};
