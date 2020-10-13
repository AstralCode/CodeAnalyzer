#pragma once

#include "CodeAnalyzerModule.h"

/*
	### Module Description ###
	This module calculates the total number of lines of code
	in the header and source files.
*/
class CCodeFileLineCountModule final : public CCodeAnalyzerModule
{
public:
	CCodeFileLineCountModule();

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile ) override;
};
