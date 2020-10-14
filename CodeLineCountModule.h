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
	CCodeLineCountModule();

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile ) override;

private:
	enum EStatisticsId
	{
		eTotalCodeLineCount
	};
};
