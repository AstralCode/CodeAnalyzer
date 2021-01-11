#pragma once

#include <set>

#include "CodeAnalyzerModule.h"
#include "Function.h"

/*
	### Description ###
	This module separately count the number of lines code of
	global and member functions (including constructors and destructors).
	The line count ranges are split by page length:
	[0] -> <0-16>		[QP]  -> Quarter page
	[1] -> <17-32>		[HP]  -> Half page
	[2] -> <33-62>		[1P]  -> 1 page
	[3] -> <63-124>		[2P]  -> 2 page
	[4] -> <125-248>	[4P]  -> 4 page
	[5] -> <249-more>	[4P+] -> 5 and more pages
*/
class CFunctionLengthModule final : public CCodeAnalyzerModule
{
public:
	using CCodeAnalyzerModule::CCodeAnalyzerModule;

	void OnPreExecute() override;

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile ) override;

	void OnPostExecute( CStatisticsCollection& oFinalStatisticsCollection ) override;

	void OnCollectedStatistics( CStatisticsCollection& oFinalStatisticsCollection ) override;

private:
	void CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector );

	std::set<SFindDataResult<CFunction>> m_oFunctionSet;
};
