#pragma once

#include <array>

#include "CodeAnalyzerModule.h"
#include "FindDataResult.h"
#include "Variable.h"

/*
	### Description ###
	This module calculates the total number of
	global variables in the source files only.
*/
class CVariableGlobalCountModule final : public CCodeAnalyzerModule
{
public:
	void OnPreExecute( CStatisticsCollection& oStatisticsCollection ) override;

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile, CStatisticsCollection& oStatisticsCollection ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection ) override;

	void OnPostExecute( CStatisticsCollection& oStatisticsCollection ) override;

private:
	static std::array<std::string_view, 19u> aszExcludedVariableType;

	void PrepareVariableType( std::string& oVariableTypeString ) const;
	void FilterVariableTypes( std::vector<SFindDataResult<CVariable>>& oVariableVector ) const;
};