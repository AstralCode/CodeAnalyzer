#include "VariableGlobalCountModule.h"

#include <algorithm>

#include "SourceFile.h"
#include "StatisticsCollection.h"
#include "StringHelper.h"

std::array<std::string_view, 19u> CVariableGlobalCountModule::aszExcludedVariableType =
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
// void CVariableGlobalCountModule::OnPreExecute
// 3BGO JIRA-238 22-10-2020
void CVariableGlobalCountModule::OnPreExecute( CStatisticsCollection& oStatisticsCollection )
{
    oStatisticsCollection[EStatisticsTypes::eGlobalVariableCount].oHeaderString = "Global Variables";
}

// ^^x
// void CVariableGlobalCountModule::ProcessHeaderFile
// 3BGO JIRA-238 22-10-2020
void CVariableGlobalCountModule::ProcessHeaderFile( const CHeaderFile&, CStatisticsCollection& )
{

}

// ^^x
// void CVariableGlobalCountModule::ProcessSourceFile
// 3BGO JIRA-238 22-10-2020
void CVariableGlobalCountModule::ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection )
{
    std::vector<SFindDataResult<CVariable>> oGlobalVariableVector = oSourceFile.GetGlobalVariables();
    FilterVariableTypes( oGlobalVariableVector );
    
    oStatisticsCollection[EStatisticsTypes::eGlobalVariableCount].uiValue += oGlobalVariableVector.size();
}

// ^^x
// void CVariableGlobalCountModule::OnPostExecute
// 3BGO JIRA-238 22-10-2020
void CVariableGlobalCountModule::OnPostExecute( CStatisticsCollection& )
{

}

// ^^x
// void CVariableGlobalCountModule::ProcessSourceFile
// 3BGO JIRA-238 22-10-2020
void CVariableGlobalCountModule::PrepareVariableType( std::string& oVariableTypeString ) const
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
// void CVariableGlobalCountModule::FilterVariableTypes
// 3BGO JIRA-238 22-10-2020
void CVariableGlobalCountModule::FilterVariableTypes( std::vector<SFindDataResult<CVariable>>& oVariableVector ) const
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
