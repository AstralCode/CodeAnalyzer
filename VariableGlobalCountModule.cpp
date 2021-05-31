#include "VariableGlobalCountModule.h"

#include <algorithm>

#include "SourceFile.h"
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
void CVariableGlobalCountModule::OnPreExecute()
{
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eGlobalSimpleVariableCount, "Global Simple Variables" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eGlobalObjectsCount, "Global Objects" );
}

// ^^x
// void CVariableGlobalCountModule::ProcessHeaderFile
// 3BGO NTP-1 22-10-2020
void CVariableGlobalCountModule::ProcessHeaderFile( const CHeaderFile& )
{

}

// ^^x
// void CVariableGlobalCountModule::ProcessSourceFile
// 3BGO NTP-1 22-10-2020
void CVariableGlobalCountModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    std::vector<SFindDataResult<CVariable>> oGlobalVariableVector = oSourceFile.GetGlobalVariables();

    if ( !oGlobalVariableVector.empty() )
    {
        FilterVariables( oGlobalVariableVector );

        for ( const SFindDataResult<CVariable>& oVariable : oGlobalVariableVector )
        {
            std::string oVariableTypeString = CStringHelper::Trim( oVariable.oData.GetType() );

            oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "static" );
            oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "constexpr" );
            oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "const" );
            oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "unsigned" );
            oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "*" );
            oVariableTypeString = CStringHelper::Remove( oVariableTypeString, "&" );
            oVariableTypeString = CStringHelper::Trim( oVariableTypeString );

            if ( !std::islower( oVariableTypeString[0], {} ) && oVariableTypeString[0] == 'C' && oVariableTypeString != "CHAR" )
            {
                m_oGlobalObjectsSet.insert( oVariable );
            }
            else
            {
                m_oGlobalSimpleVariableSet.insert( oVariable );
            }
        }
    }
}

// ^^x
// void CVariableGlobalCountModule::OnPostExecute
// 3BGO NTP-1 22-10-2020
void CVariableGlobalCountModule::OnPostExecute( CStatisticsCollection& oFinalStatisticsCollection )
{
    m_oStatisticsCollection.SetStatisticsValue( EStatisticsTypes::eGlobalSimpleVariableCount, m_oGlobalSimpleVariableSet.size() );
    m_oStatisticsCollection.SetStatisticsValue( EStatisticsTypes::eGlobalObjectsCount, m_oGlobalObjectsSet.size());

    oFinalStatisticsCollection.MergeStatistics( m_oStatisticsCollection );
}

// ^^x
// void CVariableGlobalCountModule::OnCollectedStatistics
// 3BGO NTP-1 11-01-2021
void CVariableGlobalCountModule::OnCollectedStatistics( CStatisticsCollection& )
{
    if ( IsLoggingEnabled() )
    {
        if ( !m_oGlobalSimpleVariableSet.empty() || !m_oGlobalObjectsSet.empty() )
        {
            m_oLogger.Open( "GlobalVariables.txt" );

            std::for_each( m_oGlobalSimpleVariableSet.cbegin(), m_oGlobalSimpleVariableSet.cend(), [this]( const SFindDataResult<CVariable>& oVariable )
            {
                m_oLogger.Log( oVariable );
            } );

            std::for_each( m_oGlobalObjectsSet.cbegin(), m_oGlobalObjectsSet.cend(), [this](const SFindDataResult<CVariable>& oVariable )
            {
                m_oLogger.Log( oVariable );
            });
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
