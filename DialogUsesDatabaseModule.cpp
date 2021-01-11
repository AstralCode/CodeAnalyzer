#include "DialogUsesDatabaseModule.h"

#include "SourceFile.h"
#include "Utility.h"

std::array<std::string_view, 2u> CDialogUsesDatabaseModule::aszDialogDatabaseIdentifiers =
{
    "Dialog",
    "Dlg",
};

std::array<std::string_view, 8u> CDialogUsesDatabaseModule::aszDatabaseFunctionNames =
{
    "DbOpen",
    "DbClose",
    "DbCreateRecord",
    "DbFindRecord",
    "DbFindFirstRecord",
    "DbSaveRecord",
    "DbUnlockRecord",
    "DbGetStatus"
};

// ^^x
// void CDialogUsesDatabaseModule::OnPreExecute
// 3BGO NTP-1 24-10-2020
void CDialogUsesDatabaseModule::OnPreExecute()
{
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eDialogClassesCount, "Dialogs" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eDialogUsesDatabaseCount, "Dialogs using database" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eDialogUsesDatabasePercent, "%" );
}

// ^^x
// void CDialogUsesDatabaseModule::ProcessHeaderFile
// 3BGO NTP-1 24-10-2020
void CDialogUsesDatabaseModule::ProcessHeaderFile( const CHeaderFile& )
{

}

// ^^x
// void CDialogUsesDatabaseModule::ProcessSourceFile
// 3BGO NTP-1 24-10-2020
void CDialogUsesDatabaseModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    const std::vector<SFindDataResult<CFunction>> oMemberFunctionVector = oSourceFile.GetMemberFunctions();

    for ( const SFindDataResult<CFunction>& oMemberFunction : oMemberFunctionVector )
    {
        ProcessMemberFunction( oMemberFunction );
    }
}

// ^^x
// void CDialogUsesDatabaseModule::OnPostExecute
// 3BGO NTP-1 24-10-2020
void CDialogUsesDatabaseModule::OnPostExecute( CStatisticsCollection& oFinalStatisticsCollection )
{
    m_oStatisticsCollection.SetStatisticsValue( EStatisticsTypes::eDialogClassesCount, m_oDialogClassSet.size() );
    m_oStatisticsCollection.SetStatisticsValue( EStatisticsTypes::eDialogUsesDatabaseCount, m_oDialogClassUsesDatabaseSet.size() );

    oFinalStatisticsCollection.MergeStatistics( m_oStatisticsCollection );
}

// ^^x
// void CDialogUsesDatabaseModule::OnCollectedStatistics
// 3BGO NTP-1 11-01-2021
void CDialogUsesDatabaseModule::OnCollectedStatistics( CStatisticsCollection& oFinalStatisticsCollection )
{
    const SStatisticsResult::ValueType uiDialogCount = oFinalStatisticsCollection.GetStatisticsValue( EStatisticsTypes::eDialogClassesCount );
    const SStatisticsResult::ValueType uiDialogUsesDatabaseCount = oFinalStatisticsCollection.GetStatisticsValue( EStatisticsTypes::eDialogUsesDatabaseCount );

    const SStatisticsResult::ValueType uiDialogCountPercent = ToPercent( uiDialogUsesDatabaseCount, uiDialogCount );
    oFinalStatisticsCollection.SetStatisticsValue( EStatisticsTypes::eDialogUsesDatabasePercent, uiDialogCountPercent );

    if ( IsLoggingEnabled() )
    {
        if ( !m_oDialogClassUsesDatabaseSet.empty() )
        {
            m_oLogger.Open( "DialogsUsingDatabase.txt" );

            std::for_each( m_oDialogClassUsesDatabaseSet.cbegin(), m_oDialogClassUsesDatabaseSet.cend(), [this]( const std::string& oClassNameString )
            {
                m_oLogger.WriteLine( oClassNameString );
            } );
        }
    }
}

// ^^x
// void CDialogUsesDatabaseModule::ProcessMemberFunction
// 3BGO NTP-1 24-10-2020
void CDialogUsesDatabaseModule::ProcessMemberFunction( const SFindDataResult<CFunction>& oMemberFunction )
{
    std::string oClassNameString{};
    std::string oFunctionBodyString{};

    if ( ContainsClassName( oMemberFunction, oClassNameString ) && IsDialogClass( oClassNameString ) )
    {
        m_oDialogClassSet.insert( oClassNameString );

        if ( !IsDialogClassExcluded( oClassNameString ) )
        {
            if ( ContainsFunctionBody( oMemberFunction, oFunctionBodyString ) )
            {
                if ( IsMemberFunctionBodyUsesDatabase( oFunctionBodyString ) )
                {
                    m_oDialogClassUsesDatabaseSet.insert( oClassNameString );
                }
            }
        }
    }
}

// ^^x
// bool CDialogUsesDatabaseModule::ContainsClassName
// 3BGO NTP-1 24-10-2020
bool CDialogUsesDatabaseModule::ContainsClassName( const SFindDataResult<CFunction>& oMemberFunction, std::string& oClassNameString ) const
{
    bool bHasClassName = oMemberFunction.oData.GetClassName().has_value();
    if ( bHasClassName )
    {
        oClassNameString = *oMemberFunction.oData.GetClassName();
    }

    return bHasClassName;
}

// ^^x
// bool CDialogUsesDatabaseModule::ContainsFunctionBody
// 3BGO NTP-1 24-10-2020
bool CDialogUsesDatabaseModule::ContainsFunctionBody( const SFindDataResult<CFunction>& oMemberFunction, std::string& oFunctionBodyString ) const
{
    bool bHasFunctionBody = oMemberFunction.oData.GetBody().has_value();
    if ( bHasFunctionBody )
    {
        oFunctionBodyString = *oMemberFunction.oData.GetBody();
    }

    return bHasFunctionBody;
}

// ^^x
// bool CDialogUsesDatabaseModule::IsMemberFunctionBodyUsesDatabase
// 3BGO NTP-1 24-10-2020
bool CDialogUsesDatabaseModule::IsMemberFunctionBodyUsesDatabase( std::string& oFunctionBodyString ) const
{
    bool bIsFunctionUsesDatabase{ false };

    for ( std::string_view szDatabaseFunctionName : aszDatabaseFunctionNames )
    {
        bIsFunctionUsesDatabase = oFunctionBodyString.find( szDatabaseFunctionName ) != std::string::npos;
        if ( bIsFunctionUsesDatabase )
        {
            break;
        }
    }

    return bIsFunctionUsesDatabase;
}

// ^^x
// bool CDialogUsesDatabaseModule::IsDialogClass
// 3BGO NTP-1 24-10-2020
bool CDialogUsesDatabaseModule::IsDialogClass( const std::string& oClassNameString ) const
{
    bool bIsDialogClass{ false };

    for ( std::string_view szDialogDatabaseIdentifier : aszDialogDatabaseIdentifiers )
    {
        bIsDialogClass = oClassNameString.find( szDialogDatabaseIdentifier ) != std::string::npos;
        if ( bIsDialogClass )
        {
            break;
        }
    }

    return bIsDialogClass;
}

// ^^x
// bool CDialogUsesDatabaseModule::IsDialogClassExcluded
// 3BGO NTP-1 24-10-2020
bool CDialogUsesDatabaseModule::IsDialogClassExcluded( const std::string& oClassNameString ) const
{
    return m_oDialogClassUsesDatabaseSet.find( oClassNameString ) != m_oDialogClassUsesDatabaseSet.cend();
}
