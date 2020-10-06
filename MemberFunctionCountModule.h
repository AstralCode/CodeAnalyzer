#pragma once

#include "StatisticsAnalyzerModule.h"

/*
	### Module Description ####
	This module calculates the total number of member function
	in the source files.
*/
class CMemberFunctionCountModule final : public CStatisticsAnalyzerModule
{
public:
	CMemberFunctionCountModule();

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile ) override;
};
