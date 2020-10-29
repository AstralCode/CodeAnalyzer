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
	struct SVariablePrimitiveTypeNameRule
	{
		std::string oVariableTypeString;
		std::string oPrefixString;
	};

	static const std::array<SVariablePrimitiveTypeNameRule, 13u> m_aoVariablePrimitiveTypeNameRules;

	void CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector, CStatisticsCollection& oStatisticsCollection );
	void ValidateVariables( const std::vector<SFindDataResult<CVariable>>& oVariableVector, CStatisticsCollection& oStatisticsCollection ) const;

	std::string CorrectPrefixName( const CVariable& oVariable, const SVariablePrimitiveTypeNameRule& oVariableNameRule ) const;
	std::string SimplifyVariableType( const CVariable& oVariable ) const;

	bool IsVariableNameCorrect( const CVariable& oVariable, const SVariablePrimitiveTypeNameRule& oVariableNameRule ) const;
	bool IsVariableNameFirstCharacterCorrect( const CVariable& oVariable, const SVariablePrimitiveTypeNameRule& oVariableNameRule ) const;
	bool IsVariablePrefixNameCorrect( const CVariable& oVariable, const SVariablePrimitiveTypeNameRule& oVariableNameRule ) const;
	bool HasVariablePrimitiveType( const CVariable& oVariable, SVariablePrimitiveTypeNameRule& oVariableNameRule ) const;
};
