#pragma once

#include "CodeAnalyzerModule.h"

/*
	### Description ###
	This module calculates the total number of global
	functions and variables in the source files only.
*/
class CGlobalCountModule final : public CCodeAnalyzerModule
{
public:
	CGlobalCountModule();

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile ) override;

private:
	enum EStatisticsId
	{
		eGlobalVariables,
		eGlobalFunctions
	};
};
