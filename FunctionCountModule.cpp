#include "FunctionCountModule.h"

#include "SourceFile.h"
#include "Utility.h"

// ^^x
// void CFunctionLengthModule::OnPreExecute
// 3BGO NTP-1 23-10-2020
void CFunctionCountModule::OnPreExecute()
{
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eFunctionCount, "Functions" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eGlobalFunctionCount, "Global Functions" );
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eGlobalFunctionPercent, "%" );
}

// ^^x
// void CFunctionCountModule::ProcessHeaderFile
// 3BGO NTP-1 01-10-2020
void CFunctionCountModule::ProcessHeaderFile( const CHeaderFile& )
{

}

// ^^x
// void CFunctionCountModule::ProcessSourceFile
// 3BGO NTP-1 24-09-2020
void CFunctionCountModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    const std::size_t uiMemberFunctionCount = oSourceFile.GetMemberFunctions().size();
    const std::size_t uiGlobalFunctionCount = oSourceFile.GetGlobalFunctions().size();

    m_oStatisticsCollection.AccumulateStatisticsValue( EStatisticsTypes::eFunctionCount, ( uiMemberFunctionCount + uiGlobalFunctionCount ) );
    m_oStatisticsCollection.AccumulateStatisticsValue( EStatisticsTypes::eGlobalFunctionCount, uiGlobalFunctionCount );
}

// ^^x
// void CFunctionCountModule::OnPostExecute
// 3BGO NTP-1 23-10-2020
void CFunctionCountModule::OnPostExecute( CStatisticsCollection& oFinalStatisticsCollection )
{
    oFinalStatisticsCollection.MergeStatistics( m_oStatisticsCollection );
}

// ^^x
// void CFunctionCountModule::OnCollectedStatistics
// 3BGO NTP-1 11-01-2021
void CFunctionCountModule::OnCollectedStatistics( CStatisticsCollection& oFinalStatisticsCollection )
{
    const SStatisticsResult::ValueType uiFunctionCount = oFinalStatisticsCollection.GetStatisticsValue( EStatisticsTypes::eFunctionCount );
    const SStatisticsResult::ValueType uiGlobalFunctionCount = oFinalStatisticsCollection.GetStatisticsValue( EStatisticsTypes::eGlobalFunctionCount );

    const SStatisticsResult::ValueType uiGlobalFunctionCountPercent = ToPercent( uiGlobalFunctionCount, uiFunctionCount );
    oFinalStatisticsCollection.SetStatisticsValue( EStatisticsTypes::eGlobalFunctionPercent, uiGlobalFunctionCountPercent );
}
