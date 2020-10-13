#pragma once

#include "StatisticsAnalyzerModule.h"

/*
	### Module Description ####
	This module calculates the total number of global and member functions
	in the source files.
*/
class CFunctionCountModule final : public CStatisticsAnalyzerModule
{
public:
	CFunctionCountModule();

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile ) override;
};
