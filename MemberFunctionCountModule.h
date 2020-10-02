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
	CMemberFunctionCountModule( CCodeParser& oCodeParser );

	void PreProcessCodeFile( const CCodeFile& oCodeFile ) override;
	void ProcessCodeFile( const CCodeFile& oCodeFile ) override;
	void PostProcessCodeFile( const CCodeFile& oCodeFile ) override;

	std::string GetModuleName() const override;
};
