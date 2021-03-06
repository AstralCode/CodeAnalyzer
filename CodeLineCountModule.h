#pragma once

#include "CodeAnalyzerModule.h"

/*
	### Description ###
	This module calculates the total number of lines of code
	in the header and source files.
*/
class CCodeLineCountModule final : public CCodeAnalyzerModule
{
public:
	void OnPreExecute( CStatisticsCollection& oStatisticsCollection ) override;

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile, CStatisticsCollection& oStatisticsCollection ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection ) override;

	void OnPostExecute( CStatisticsCollection& oStatisticsCollection ) override;
};
