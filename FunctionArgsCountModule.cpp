#include "FunctionArgsCountModule.h"

#include "SourceFile.h"
#include "StringHelper.h"
#include "Utility.h"

// ^^x
// void CFunctionLengthModule::OnPreExecute
// 3BGO NTP-1 22-10-2020
void CFunctionArgsCountModule::OnPreExecute()
{
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eFunction6PlusArgsCount, "Functions Args 6+" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eFunction6PlusArgsPercent, "%" );
}

// ^^x
// void CFunctionLengthModule::ProcessHeaderFile
// 3BGO NTP-1 22-10-2020
void CFunctionArgsCountModule::ProcessHeaderFile( const CHeaderFile& )
{

}

// ^^x
// void CFunctionLengthModule::ProcessSourceFile
// 3BGO NTP-1 22-10-2020
void CFunctionArgsCountModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    CalculateStatistics( oSourceFile.GetGlobalFunctions() );
    CalculateStatistics( oSourceFile.GetMemberFunctions() );
}

// ^^x
// void CFunctionLengthModule::OnPostExecute
// 3BGO NTP-1 22-10-2020
void CFunctionArgsCountModule::OnPostExecute( CStatisticsCollection& oFinalStatisticsCollection )
{
    m_oStatisticsCollection.SetStatisticsValue( EStatisticsTypes::eFunction6PlusArgsCount, m_oFunctionSet.size() );

    oFinalStatisticsCollection.MergeStatistics( m_oStatisticsCollection );
}

// ^^x
// void CFunctionArgsCountModule::OnCollectedStatistics
// 3BGO NTP-1 11-01-2021
void CFunctionArgsCountModule::OnCollectedStatistics( CStatisticsCollection& oFinalStatisticsCollection )
{
    const SStatisticsResult::ValueType uiFunctionCount = oFinalStatisticsCollection.GetStatisticsValue( EStatisticsTypes::eFunctionCount );
    const SStatisticsResult::ValueType uiFunction6PlusArgsCount = oFinalStatisticsCollection.GetStatisticsValue( EStatisticsTypes::eFunction6PlusArgsCount );

    const SStatisticsResult::ValueType uiFunction6PlusArgsCountPercent = ToPercent( uiFunction6PlusArgsCount, uiFunctionCount );
    oFinalStatisticsCollection.SetStatisticsValue( EStatisticsTypes::eFunction6PlusArgsPercent, uiFunction6PlusArgsCountPercent );

    if ( IsLoggingEnabled() )
    {
        if ( !m_oFunctionSet.empty() )
        {
            m_oLogger.Open( "FunctionsArgs6Plus.txt" );

            std::for_each( m_oFunctionSet.cbegin(), m_oFunctionSet.cend(), [this]( const SFindDataResult<CFunction>& oFunction )
            {
                m_oLogger.Log( oFunction );
                m_oLogger.WriteLine();
            } );
        }
    }
}

// ^^x
// void CFunctionLengthModule::CalculateStatistics
// 3BGO NTP-1 22-10-2020
void CFunctionArgsCountModule::CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector )
{
    for ( const SFindDataResult<CFunction>& oFunction : oFunctionVector )
    {
        if ( oFunction.oData.GetArgumentList().has_value() )
        {
            const std::size_t uiFunctionCodeLineCount = CStringHelper::Split( *oFunction.oData.GetArgumentList(), ',' ).size();
            if ( uiFunctionCodeLineCount >= 6u )
            {
                m_oFunctionSet.insert( oFunction );
            }
        }
    }
}
