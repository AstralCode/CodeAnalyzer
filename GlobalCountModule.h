#pragma once

#include <array>

#include "CodeAnalyzerModule.h"
#include "FindDataResult.h"
#include "Variable.h"

/*
	### Description ###
	This module calculates the total number of global
	functions and variables in the source files only.

	Note: The module uses exclude type list,
	which are not treat as Global variable, eq.
	primitive types like char, int, short, long, etc.
*/
class CGlobalCountModule final : public CCodeAnalyzerModule
{
public:
	void OnExcute( CStatisticsCollection& oStatisticsCollection ) override;

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile, CStatisticsCollection& oStatisticsCollection ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection ) override;

	void OnExcuteComplete( CStatisticsCollection& oStatisticsCollection ) override;

private:
	static std::array<std::string_view, 19u> aszExcludedVariableType;

	void PrepareVariableType( std::string& oVariableTypeString ) const;
	void FilterVariableTypes( std::vector<SFindDataResult<CVariable>>& oVariableVector ) const;
};
