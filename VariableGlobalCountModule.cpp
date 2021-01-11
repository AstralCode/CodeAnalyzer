#include "VariableGlobalCountModule.h"

#include <algorithm>

#include "SourceFile.h"
#include "StatisticsCollection.h"
#include "StringHelper.h"

std::array<std::string_view, 3u> CVariableGlobalCountModule::oExcludedVariableTypeKeywordArray =
{
    "extern", "constexpr", "const"
};

std::array<std::string_view, 5u> CVariableGlobalCountModule::oExcludedVariableTypeArray =
{
    "PCTSTR", "PCUTSTR", "LPCSTR", "LPCTSTR", "LPCUTSTR"
};

std::array<std::string_view, 1u> CVariableGlobalCountModule::oExcludedVariableNameArray =
{
    "THIS_FILE"
};

// ^^x
// void CVariableGlobalCountModule::OnPreExecute
// 3BGO NTP-1 22-10-2020
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
// 3BGO NTP-1 22-10-2020
void CVariableGlobalCountModule::ProcessHeaderFile( const CHeaderFile&, CStatisticsCollection& )
{

}

// ^^x
// void CVariableGlobalCountModule::ProcessSourceFile
// 3BGO NTP-1 22-10-2020
void CVariableGlobalCountModule::ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection )
{
    std::vector<SFindDataResult<CVariable>> oGlobalVariableVector = oSourceFile.GetGlobalVariables();

    if ( !oGlobalVariableVector.empty() )
    {
        FilterVariables( oGlobalVariableVector );

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
// 3BGO NTP-1 22-10-2020
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
// void CVariableGlobalCountModule::FilterVariables
// 3BGO NTP-1 22-10-2020
void CVariableGlobalCountModule::FilterVariables( std::vector<SFindDataResult<CVariable>>& oVariableVector ) const
{
    std::vector<SFindDataResult<CVariable>>::iterator oRemoveResultIt = std::remove_if( oVariableVector.begin(), oVariableVector.end(), [this]( const SFindDataResult<CVariable>& oVariable )
    {
        if ( ContainsExcludedKeyword( oVariable.oData ) )
        {
            return true;
        }

        if ( ContainsExcludedType( oVariable.oData ) )
        {
            return true;
        }

        if ( ContainsExcludedName( oVariable.oData ) )
        {
            return true;
        }

        return false;
    } );

    oVariableVector.erase( oRemoveResultIt, oVariableVector.cend() );
}

// ^^x
// bool CVariableGlobalCountModule::ContainsExcludedKeyword
// 3BGO NTP-1 09-12-2020
bool CVariableGlobalCountModule::ContainsExcludedKeyword( const CVariable& oVariable ) const
{
    const std::string oVariableTypeString = oVariable.GetType();

    for ( std::string_view oExcludedKeywordString : oExcludedVariableTypeKeywordArray )
    {
        if ( oVariableTypeString.find( oExcludedKeywordString ) != std::string::npos )
        {
            return true;
        }
    }

    return false;
}

// ^^x
// bool CVariableGlobalCountModule::ContainsExcludedType
// 3BGO NTP-1 09-12-2020
bool CVariableGlobalCountModule::ContainsExcludedType( const CVariable& oVariable ) const
{
    const std::string oVariableTypeString = oVariable.GetType();

    for ( std::string_view oExcludedTypeString : oExcludedVariableTypeArray )
    {
        if ( oVariableTypeString.find( oExcludedTypeString ) != std::string::npos )
        {
            return true;
        }
    }

    return false;
}

// ^^x
// bool CVariableGlobalCountModule::ContainsExcludedName
// 3BGO NTP-1 09-12-2020
bool CVariableGlobalCountModule::ContainsExcludedName( const CVariable& oVariable ) const
{
    const std::string oVariableNameString = CStringHelper::ToLowerCase( oVariable.GetName() );

    for ( std::string_view oExcludedNameString : oExcludedVariableNameArray )
    {
        if ( oVariableNameString.find( CStringHelper::ToLowerCase( std::string{ oExcludedNameString } ) ) != std::string::npos )
        {
            return true;
        }
    }

    return false;
}
