#pragma once

#include <array>

#include "CodeAnalyzerModule.h"
#include "FindDataResult.h"
#include "Variable.h"

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
		eGlobalVariables
	};

	static std::array<std::string_view, 19u> aszExcludedVariableType;

	void PrepareVariableType( std::string& oVariableTypeString ) const;
	void FilterVariableTypes( std::vector<SFindDataResult<CVariable>>& oVariableVector ) const;
};
