#include "CodeLineCountModule.h"

#include "HeaderFile.h"
#include "SourceFile.h"

// ^^x
// void CCodeLineCountModule::OnPreExecute
// 3BGO NTP-1 24-09-2020
void CCodeLineCountModule::OnPreExecute()
{
    m_oStatisticsCollection.AddStatistics( EStatisticsTypes::eCodeLineCount, "Code Lines" );
}

// ^^x
// void CCodeLineCountModule::ProcessHeaderFile
// 3BGO NTP-1 24-09-2020
void CCodeLineCountModule::ProcessHeaderFile( const CHeaderFile& oHeaderFile )
{
    m_oStatisticsCollection.AccumulateStatisticsValue( EStatisticsTypes::eCodeLineCount, oHeaderFile.GetCodeLineCount() );
}

// ^^x
// void CCodeLineCountModule::ProcessSourceFile
// 3BGO NTP-1 24-09-2020
void CCodeLineCountModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    m_oStatisticsCollection.AccumulateStatisticsValue( EStatisticsTypes::eCodeLineCount, oSourceFile.GetCodeLineCount() );
}

// ^^x
// void CCodeLineCountModule::OnPostExecute
// 3BGO NTP-1 24-09-2020
void CCodeLineCountModule::OnPostExecute( CStatisticsCollection& oFinalStatisticsCollection )
{
    oFinalStatisticsCollection.MergeStatistics( m_oStatisticsCollection );
}

// ^^x
// void CCodeLineCountModule::OnCollectedStatistics
// 3BGO NTP-1 11-01-2021
void CCodeLineCountModule::OnCollectedStatistics( CStatisticsCollection& )
{

}
