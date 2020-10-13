#pragma once

#include <algorithm>

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

	template<typename T>
	bool IsValueContainsInRange( const T uiValue, const T uiMin, const T uiMax = std::numeric_limits<T>::max() ) const;

	std::string m_oDeveloperString;
};

// ^^x
// bool CDeveloperAnalyzerModule::IsValueContainsInRange
// 3BGO JIRA-238 05-10-2020
template<typename T>
inline bool CDeveloperAnalyzerModule::IsValueContainsInRange( const T uiValue, const T uiMin, const T uiMax ) const
{
	return std::clamp( uiValue, uiMin, uiMax ) == uiValue;
}
