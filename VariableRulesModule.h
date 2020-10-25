#pragma once

#include <array>

#include "CodeAnalyzerModule.h"
#include "Function.h"

/*
	### Description ###
	This module calculates the total number of variable
	definitions which not complain rules of naming variable.
*/
class CVariableRulesModule final : public CCodeAnalyzerModule
{
public:
	void OnPreExecute( CStatisticsCollection& oStatisticsCollection ) override;

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile, CStatisticsCollection& oStatisticsCollection ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection ) override;

	void OnPostExecute( CStatisticsCollection& oStatisticsCollection ) override;

private:
	struct SVariableNameRule
	{
		std::string oVariableTypeString;
		std::string oPrefixString;
		std::optional<std::string> oPostfixString;
	};

	static const std::array<SVariableNameRule, 8u> m_aoVariableNameRules;

	void CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector, CStatisticsCollection& oStatisticsCollection );
	void ValidateVariables( const std::vector<SFindDataResult<CVariable>>& oVariableVector, CStatisticsCollection& oStatisticsCollection ) const;
};
