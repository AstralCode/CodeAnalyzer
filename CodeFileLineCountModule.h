#pragma once

#include "StatisticsAnalyzerModule.h"

/*
	### Module Description ###
	This module calculates the total number of lines of code
	in the header and source files.
*/
class CCodeFileLineCountModule final : public CStatisticsAnalyzerModule
{
public:
	CCodeFileLineCountModule( CCodeParser& oCodeParser );

	void PreProcessCodeFile( const CCodeFile& oCodeFile ) override;
	void ProcessCodeFile( const CCodeFile& oCodeFile ) override;
	void PostProcessCodeFile( const CCodeFile& oCodeFile ) override;

	std::string GetModuleName() const override;
};
