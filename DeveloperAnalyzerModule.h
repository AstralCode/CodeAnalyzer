#pragma once

#include "CodeAnalyzerModule.h"

/*
	### Module Description ###
	This module is only for test.
*/
class CDeveloperAnalyzerModule final : public CCodeAnalyzerModule
{
public:
	CDeveloperAnalyzerModule( const std::string& oDeveloperString );

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile ) override;

private:
	enum EStatisticsId
	{
		eFunctions,
		eFunctionsParseError,
		eFunctionQPLength,
		eFunctionHPLength,
		eFunction1PLength,
		eFunction2PLength,
		eFunction4PLength,
		eFunction4PMoreLength
	};

	std::string m_oDeveloperString;
};
