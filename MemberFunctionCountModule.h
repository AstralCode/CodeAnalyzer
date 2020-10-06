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

	void ProcessCodeFile( const CCodeFile& oCodeFile ) override;

	std::string GetModuleName() const override;
};
