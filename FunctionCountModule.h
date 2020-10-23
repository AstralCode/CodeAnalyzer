#pragma once

#include "CodeAnalyzerModule.h"

/*
	### Description ###
	This module calculates the total number of global and member functions
	in the source files.
*/
class CFunctionCountModule final : public CCodeAnalyzerModule
{
public:
	CFunctionCountModule();

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile ) override;

	void OnComplete() override;

private:
	enum EStatisticsId
	{
		eFunctions,
		eMemberFunctions,
		eMemberFunctionsPercent,
		eGlobalFunctions,
		eGlobalFunctionsPercent
	};
};
