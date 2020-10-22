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
	CFunctionArgsCountModule();

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile ) override;

private:
	enum EStatisticsId
	{
		eFunctionArgs5MoreCount
	};

	void CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector );
};
