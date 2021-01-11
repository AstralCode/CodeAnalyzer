#pragma once

#include <array>
#include <set>

#include "CodeAnalyzerModule.h"
#include "FindDataResult.h"
#include "Variable.h"

/*
	### Description ###
	This module calculates the total number of global variables in the source files only.
	Note: One global object can itself contains multiple objects which are also treat as global objects.
*/
class CVariableGlobalCountModule final : public CCodeAnalyzerModule
{
public:
	using CCodeAnalyzerModule::CCodeAnalyzerModule;

	void OnPreExecute() override;

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile ) override;

	void OnPostExecute( CStatisticsCollection& oFinalStatisticsCollection ) override;

	void OnCollectedStatistics( CStatisticsCollection& oFinalStatisticsCollection ) override;

private:
	static std::array<std::string_view, 3u> oExcludedVariableTypeKeywordArray;
	static std::array<std::string_view, 5u> oExcludedVariableTypeArray;
	static std::array<std::string_view, 1u> oExcludedVariableNameArray;

	void FilterVariables( std::vector<SFindDataResult<CVariable>>& oVariableVector ) const;

	bool ContainsExcludedKeyword( const CVariable& oVariable ) const;
	bool ContainsExcludedType( const CVariable& oVariable ) const;
	bool ContainsExcludedName( const CVariable& oVariable ) const;

	std::set<SFindDataResult<CVariable>> m_oGlobalVariableSet;
};
