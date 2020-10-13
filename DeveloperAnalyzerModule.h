#pragma once

#include "CodeAnalyzerModule.h"

/*
	### Module Description ###
	This module is only for test.
*/
class CDeveloperAnalyzerModule final : public CCodeAnalyzerModule
{
public:
	CDeveloperAnalyzerModule( const std::string& oDeveloperString, const unsigned int uiCodeFileCount );

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile ) override;

private:
	enum EStatisticsId
	{
		eFiles,
		eFunctions,
		eFunctionQPLength,
		eFunctionHPLength,
		eFunction1PLength,
		eFunction2PLength,
		eFunction4PLength,
		eFunction4PMoreLength,
		eFunctionsParseError
	};

	std::string m_oDeveloperString;
};
