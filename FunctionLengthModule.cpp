#include "FunctionLengthModule.h"

#include "SourceFile.h"
#include "StringHelper.h"
#include "Utility.h"

// ^^x
// void CFunctionLengthModule::OnPreExecute
// 3BGO NTP-1 30-09-2020
void CFunctionLengthModule::OnPreExecute()
{
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eFunctionLengthQPCount, "Functions QP" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eFunctionLengthQPPercent, "%" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eFunctionLengthHPCount, "Functions HP" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eFunctionLengthHPPercent, "%" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eFunctionLength1PCount, "Functions 1P" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eFunctionLength1PPercent, "%" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eFunctionLength2PCount, "Functions 2P" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eFunctionLength2PPercent, "%" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eFunctionLength4PCount, "Functions 4P" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eFunctionLength4PPercent, "%" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eFunctionLength4PPlusCount, "Functions 5P+" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eFunctionLength4PPlusPercent, "%" );
}

// ^^x
// void CFunctionLengthModule::ProcessHeaderFile
// 3BGO NTP-1 30-09-2020
void CFunctionLengthModule::ProcessHeaderFile( const CHeaderFile& )
{

}

// ^^x
// void CFunctionLengthModule::ProcessSourceFile
// 3BGO NTP-1 24-09-2020
void CFunctionLengthModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    CalculateStatistics( oSourceFile.GetGlobalFunctions() );
    CalculateStatistics( oSourceFile.GetMemberFunctions() );
}

// ^^x
// void CFunctionLengthModule::OnPostExecute
// 3BGO NTP-1 30-09-2020
void CFunctionLengthModule::OnPostExecute( CStatisticsCollection& oFinalStatisticsCollection )
{
    oFinalStatisticsCollection.MergeStatistics( m_oStatisticsCollection );
}

// ^^x
// void CFunctionLengthModule::OnCollectedStatistics
// 3BGO NTP-1 11-01-2021
void CFunctionLengthModule::OnCollectedStatistics( CStatisticsCollection& oFinalStatisticsCollection )
{
    const SStatisticsResult::ValueType uiFunctionCount = oFinalStatisticsCollection.GetStatisticsValue( EStatisticsTypes::eFunctionCount );

    const SStatisticsResult::ValueType uiFunctionLengthQPCount = oFinalStatisticsCollection.GetStatisticsValue( EStatisticsTypes::eFunctionLengthQPCount );
    const SStatisticsResult::ValueType uiFunctionLengthQPCountPercent = ToPercent( uiFunctionLengthQPCount, uiFunctionCount );
    oFinalStatisticsCollection.SetStatisticsValue( EStatisticsTypes::eFunctionLengthQPPercent, uiFunctionLengthQPCountPercent );

    const SStatisticsResult::ValueType uiFunctionLengthHPCount = oFinalStatisticsCollection.GetStatisticsValue( EStatisticsTypes::eFunctionLengthHPCount );
    const SStatisticsResult::ValueType uiFunctionLengthHPCountPercent = ToPercent( uiFunctionLengthHPCount, uiFunctionCount );
    oFinalStatisticsCollection.SetStatisticsValue( EStatisticsTypes::eFunctionLengthHPPercent, uiFunctionLengthHPCountPercent );

    const SStatisticsResult::ValueType uiFunctionLength1PCount = oFinalStatisticsCollection.GetStatisticsValue( EStatisticsTypes::eFunctionLength1PCount );
    const SStatisticsResult::ValueType uiFunctionLength1PCountPercent = ToPercent( uiFunctionLength1PCount, uiFunctionCount );
    oFinalStatisticsCollection.SetStatisticsValue( EStatisticsTypes::eFunctionLength1PPercent, uiFunctionLength1PCountPercent );

    const SStatisticsResult::ValueType uiFunctionLength2PCount = oFinalStatisticsCollection.GetStatisticsValue( EStatisticsTypes::eFunctionLength2PCount );
    const SStatisticsResult::ValueType uiFunctionLength2PCountPercent = ToPercent( uiFunctionLength2PCount, uiFunctionCount );
    oFinalStatisticsCollection.SetStatisticsValue( EStatisticsTypes::eFunctionLength2PPercent, uiFunctionLength2PCountPercent );

    const SStatisticsResult::ValueType uiFunctionLength4PCount = oFinalStatisticsCollection.GetStatisticsValue( EStatisticsTypes::eFunctionLength4PCount );
    const SStatisticsResult::ValueType uiFunctionLength4PCountPercent = ToPercent( uiFunctionLength4PCount, uiFunctionCount );
    oFinalStatisticsCollection.SetStatisticsValue( EStatisticsTypes::eFunctionLength4PPercent, uiFunctionLength4PCountPercent );

    const SStatisticsResult::ValueType uiFunctionLength4PPlusCount = oFinalStatisticsCollection.GetStatisticsValue( EStatisticsTypes::eFunctionLength4PPlusCount );
    const SStatisticsResult::ValueType uiFunctionLength4PPlusCountPercent = ToPercent( uiFunctionLength4PPlusCount, uiFunctionCount );
    oFinalStatisticsCollection.SetStatisticsValue( EStatisticsTypes::eFunctionLength4PPlusPercent, uiFunctionLength4PPlusCountPercent );

    if ( IsLoggingEnabled() )
    {
        if ( !m_oFunctionSet.empty() )
        {
            m_oLogger.Open( "Functions2Plus.txt" );

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
// 3BGO NTP-1 24-09-2020
void CFunctionLengthModule::CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector )
{
    for ( const SFindDataResult<CFunction>& oFunction : oFunctionVector )
    {
        if ( oFunction.oData.GetBody().has_value() )
        {
            std::size_t uiFunctionCodeLineCount = CStringHelper::SplitLines( *oFunction.oData.GetBody() ).size();

            if ( uiFunctionCodeLineCount > 0u )
            {
                if ( uiFunctionCodeLineCount >= 2u )
                {
                    uiFunctionCodeLineCount -= 2u;
                }

                if ( SRange::Contains( uiFunctionCodeLineCount, { 0u }, { 16u } ) )
                {
                    m_oStatisticsCollection.AccumulateStatisticsValue( EStatisticsTypes::eFunctionLengthQPCount, 1u );
                }
                else if ( SRange::Contains( uiFunctionCodeLineCount, { 17u }, { 32u } ) )
                {
                    m_oStatisticsCollection.AccumulateStatisticsValue( EStatisticsTypes::eFunctionLengthHPCount, 1u );
                }
                else if ( SRange::Contains( uiFunctionCodeLineCount, { 33u }, { 62u } ) )
                {
                    m_oStatisticsCollection.AccumulateStatisticsValue( EStatisticsTypes::eFunctionLength1PCount, 1u );
                }
                else if ( SRange::Contains( uiFunctionCodeLineCount, { 63u }, { 124u } ) )
                {
                    m_oStatisticsCollection.AccumulateStatisticsValue( EStatisticsTypes::eFunctionLength2PCount, 1u );
                }
                else if ( SRange::Contains( uiFunctionCodeLineCount, { 125u }, { 248u } ) )
                {
                    m_oStatisticsCollection.AccumulateStatisticsValue( EStatisticsTypes::eFunctionLength4PCount, 1u );
                    m_oFunctionSet.insert( oFunction );
                }
                else if ( SRange::Contains( uiFunctionCodeLineCount, { 249u } ) )
                {
                    m_oStatisticsCollection.AccumulateStatisticsValue( EStatisticsTypes::eFunctionLength4PPlusCount, 1u );
                    m_oFunctionSet.insert( oFunction );
                }
            }
        }
    }
}
