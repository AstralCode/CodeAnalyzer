#include "GlobalCountModule.h"

#include <algorithm>

#include "SourceFile.h"
#include "StatisticsCollection.h"
#include "StringHelper.h"

std::array<std::string_view, 19u> CGlobalCountModule::aszExcludedVariableType =
{
    "short", "SHORT", "USHORT",
    "int", "INT", "UINT",
    "long" "LONG", "ULONG",
    "char", "CHAR", "PCHAR", "TCHAR", "PTCHAR", "LPCTSTR",
    "CString", "CStringA",
    "std::size_t",
    "std::string"
};

// ^^x
// void CCodeLineCountModule::OnExcute
// 3BGO JIRA-238 22-10-2020
void CGlobalCountModule::OnExcute( CStatisticsCollection& oStatisticsCollection )
{
    oStatisticsCollection[EStatisticsTypes::eGlobalVariableCount].oHeaderString = "Global Variables";
}

// ^^x
// void CCodeLineCountModule::ProcessHeaderFile
// 3BGO JIRA-238 22-10-2020
void CGlobalCountModule::ProcessHeaderFile( const CHeaderFile&, CStatisticsCollection& )
{

}

// ^^x
// void CCodeLineCountModule::ProcessSourceFile
// 3BGO JIRA-238 22-10-2020
void CGlobalCountModule::ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection )
{
    std::vector<SFindDataResult<CVariable>> oGlobalVariableVector = oSourceFile.GetGlobalVariables();
    FilterVariableTypes( oGlobalVariableVector );
    
    oStatisticsCollection[EStatisticsTypes::eGlobalVariableCount].uiValue += oGlobalVariableVector.size();
}

// ^^x
// void CCodeLineCountModule::OnExcuteComplete
// 3BGO JIRA-238 22-10-2020
void CGlobalCountModule::OnExcuteComplete( CStatisticsCollection& )
{

}

// ^^x
// void CCodeLineCountModule::ProcessSourceFile
// 3BGO JIRA-238 22-10-2020
void CGlobalCountModule::PrepareVariableType( std::string& oVariableTypeString ) const
{
    oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "static" );
    oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "constexpr" );
    oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "const" );
    oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "unsigned" );
    oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "signed" );
    oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "*" );
    oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "&" );

    oVariableTypeString = CStringHelper::Trim( oVariableTypeString );
}

// ^^x
// void CGlobalCountModule::FilterVariableTypes
// 3BGO JIRA-238 22-10-2020
void CGlobalCountModule::FilterVariableTypes( std::vector<SFindDataResult<CVariable>>& oVariableVector ) const
{
    std::vector<SFindDataResult<CVariable>>::iterator oRemoveResultIt = std::remove_if( oVariableVector.begin(), oVariableVector.end(), [this]( const SFindDataResult<CVariable>& oVariable )
    {
        bool bExcludeVariable{ false };

        std::string oVariableTypeString = oVariable.oData.GetType();
        PrepareVariableType( oVariableTypeString );

        for ( std::string_view szExcludedVariableType : aszExcludedVariableType )
        {
            if ( oVariableTypeString == szExcludedVariableType )
            {
                return true;
            }
        }

        return bExcludeVariable;
    } );

    oVariableVector.erase( oRemoveResultIt, oVariableVector.cend() );
}
