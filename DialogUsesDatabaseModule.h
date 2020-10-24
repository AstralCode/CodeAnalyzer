#pragma once

#include <set>
#include <array>

#include "CodeAnalyzerModule.h"
#include "FindDataResult.h"
#include "Function.h"

/*
	### Description ###
	This module calculates the total number of the dialog classes
	which uses database functionality in the member functions.
*/
class CDialogUsesDatabaseModule final : public CCodeAnalyzerModule
{
public:
	void OnExcute( CStatisticsCollection& oStatisticsCollection ) override;

	void ProcessHeaderFile( const CHeaderFile& oHeaderFile, CStatisticsCollection& oStatisticsCollection ) override;
	void ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection ) override;

	void OnExcuteComplete( CStatisticsCollection& oStatisticsCollection ) override;

private:
	void ProcessMemberFunction( const SFindDataResult<CFunction>& oMemberFunction, CStatisticsCollection& oStatisticsCollection );
	void ThisDialogClassUsesDatabase( std::string& oClassNameString, CStatisticsCollection& oStatisticsCollection );

	bool ContainsClassName( const SFindDataResult<CFunction>& oMemberFunction, std::string& oClassNameString ) const;
	bool ContainsFunctionBody( const SFindDataResult<CFunction>& oMemberFunction, std::string& oFunctionBodyString ) const;
	
	bool IsMemberFunctionBodyUsesDatabase( std::string& oFunctionBodyString ) const;
	bool IsDialogClass( const std::string& oClassNameString ) const;
	bool IsDialogClassExcluded( const std::string& oClassNameString ) const;

	static std::array<std::string_view, 2u> aszDialogDatabaseIdentifiers;
	static std::array<std::string_view, 7u> aszDatabaseFunctionNames;

	std::set<std::string> m_oDialogClassSet;
	std::set<std::string> m_oDialogClassUsesDatabaseSet;
};
