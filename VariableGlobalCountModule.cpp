#include "VariableGlobalCountModule.h"

#include <algorithm>

#include "SourceFile.h"
#include "StatisticsCollection.h"
#include "StringHelper.h"

std::array<std::string_view, 8u> CVariableGlobalCountModule::aszExcludedVariableType =
{
    "extern", "constexpr", "const", "PCTSTR", "PCUTSTR", "LPCSTR", "LPCTSTR", "LPCUTSTR"
};

// ^^x
// void CVariableGlobalCountModule::OnPreExecute
// 3BGO JIRA-238 22-10-2020
void CVariableGlobalCountModule::OnPreExecute( CStatisticsCollection& oStatisticsCollection )
{
    oStatisticsCollection[EStatisticsTypes::eGlobalVariableCount].oHeaderString = "Global Variables";

    if ( IsLoggingEnabled() )
    {
        m_oLogger.Open( "GlobalVariables.txt" );
    }
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

    if ( !oGlobalVariableVector.empty() )
    {
        FilterVariableTypes( oGlobalVariableVector );

        oStatisticsCollection[EStatisticsTypes::eGlobalVariableCount].uiValue += oGlobalVariableVector.size();

        if ( IsLoggingEnabled() )
        {
            for ( const SFindDataResult<CVariable>& oVariable : oGlobalVariableVector )
            {
                m_oLogger.Log( oVariable );
            }
        }
    }
}

// ^^x
// void CVariableGlobalCountModule::OnPostExecute
// 3BGO JIRA-238 22-10-2020
void CVariableGlobalCountModule::OnPostExecute( CStatisticsCollection& oStatisticsCollection )
{
    if ( IsLoggingEnabled() )
    {
        if ( oStatisticsCollection[EStatisticsTypes::eGlobalVariableCount].uiValue == 0u )
        {
            m_oLogger.Remove();
        }
    }
}

// ^^x
// void CVariableGlobalCountModule::FilterVariableTypes
// 3BGO JIRA-238 22-10-2020
void CVariableGlobalCountModule::FilterVariableTypes( std::vector<SFindDataResult<CVariable>>& oVariableVector ) const
{
    std::vector<SFindDataResult<CVariable>>::iterator oRemoveResultIt = std::remove_if( oVariableVector.begin(), oVariableVector.end(), [this]( const SFindDataResult<CVariable>& oVariable )
    {
        const std::string oVariableTypeString = oVariable.oData.GetType();

        for ( std::string_view szExcludedVariableType : aszExcludedVariableType )
        {
            if ( oVariableTypeString.find( szExcludedVariableType ) != std::string::npos )
            {
                return true;
            }
        }

        return false;
    } );

    oVariableVector.erase( oRemoveResultIt, oVariableVector.cend() );
}
