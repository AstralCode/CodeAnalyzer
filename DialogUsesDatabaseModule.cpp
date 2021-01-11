#include "DialogUsesDatabaseModule.h"

#include "SourceFile.h"
#include "StatisticsCollection.h"
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
void CDialogUsesDatabaseModule::OnPreExecute( CStatisticsCollection& oStatisticsCollection )
{
    oStatisticsCollection[EStatisticsTypes::eDialogClassesCount].oHeaderString = "Dialogs";
    oStatisticsCollection[EStatisticsTypes::eDialogUsesDatabaseCount].oHeaderString = "Dialogs using database";
    oStatisticsCollection[EStatisticsTypes::eDialogUsesDatabasePercent].oHeaderString = "%";

    if ( IsLoggingEnabled() )
    {
        m_oLogger.Open( "DialogsUsingDatabase.txt" );
    }
}

// ^^x
// void CDialogUsesDatabaseModule::ProcessHeaderFile
// 3BGO NTP-1 24-10-2020
void CDialogUsesDatabaseModule::ProcessHeaderFile( const CHeaderFile&, CStatisticsCollection& )
{

}

// ^^x
// void CDialogUsesDatabaseModule::ProcessSourceFile
// 3BGO NTP-1 24-10-2020
void CDialogUsesDatabaseModule::ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& )
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
void CDialogUsesDatabaseModule::OnPostExecute( CStatisticsCollection& oStatisticsCollection )
{
    const std::size_t uiDialogCount = m_oDialogClassSet.size();

    oStatisticsCollection[EStatisticsTypes::eDialogClassesCount].uiValue = uiDialogCount;
    oStatisticsCollection[EStatisticsTypes::eDialogUsesDatabaseCount].uiValue = m_oDialogClassUsesDatabaseSet.size();
    oStatisticsCollection[EStatisticsTypes::eDialogUsesDatabasePercent].uiValue = ToPercent( oStatisticsCollection[EStatisticsTypes::eDialogUsesDatabaseCount].uiValue, uiDialogCount );

    if ( IsLoggingEnabled() )
    {
        if ( uiDialogCount == 0u )
        {
            m_oLogger.Remove();
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

                    if ( IsLoggingEnabled() )
                    {
                        m_oLogger.WriteLine( oClassNameString );
                    }
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
