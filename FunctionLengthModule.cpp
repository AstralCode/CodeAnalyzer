#include "FunctionLengthModule.h"

#include <cmath>

#include "SourceFile.h"
#include "StringHelper.h"
#include "Utility.h"

// ^^x
// CFunctionLengthModule::CFunctionLengthModule
// 3BGO JIRA-238 30-09-2020
CFunctionLengthModule::CFunctionLengthModule()
{
    CreateStatistics( "Functions Len. QP" );
    CreateStatistics( "Functions Len. HP" );
    CreateStatistics( "Functions Len. 1P" );
    CreateStatistics( "Functions Len. 2P" );
    CreateStatistics( "Functions Len. 4P" );
    CreateStatistics( "Functions Len. 4P+" );
}

// ^^x
// void CFunctionLengthModule::ProcessHeaderFile
// 3BGO JIRA-238 30-09-2020
void CFunctionLengthModule::ProcessHeaderFile( const CHeaderFile& )
{

}

// ^^x
// void CFunctionLengthModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CFunctionLengthModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    CalculateStatistics( oSourceFile.GetGlobalFunctions() );
    CalculateStatistics( oSourceFile.GetMemberFunctions() );
}

// ^^x
// void CFunctionLengthModule::OnComplete
// 3BGO JIRA-238 22-10-2020
void CFunctionLengthModule::OnComplete()
{
    const std::size_t uiTotalSumStatisticsValue = SumStatisticsValues();

    ToPercent( GetStatistics( EStatisticsId::eFunctionQPLength ).uiValue, uiTotalSumStatisticsValue );
    ToPercent( GetStatistics( EStatisticsId::eFunctionHPLength ).uiValue, uiTotalSumStatisticsValue );
    ToPercent( GetStatistics( EStatisticsId::eFunction1PLength ).uiValue, uiTotalSumStatisticsValue );
    ToPercent( GetStatistics( EStatisticsId::eFunction2PLength ).uiValue, uiTotalSumStatisticsValue );
    ToPercent( GetStatistics( EStatisticsId::eFunction4PLength ).uiValue, uiTotalSumStatisticsValue );
    ToPercent( GetStatistics( EStatisticsId::eFunction4PMoreLength ).uiValue, uiTotalSumStatisticsValue );
}

// ^^x
// void CFunctionLengthModule::CalculateStatistics
// 3BGO JIRA-238 24-09-2020
void CFunctionLengthModule::CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector )
{
    for ( const SFindDataResult<CFunction>& oFunction : oFunctionVector )
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
                ++GetStatistics( EStatisticsId::eFunctionQPLength ).uiValue;
            }
            else if ( SRange::Contains( uiFunctionCodeLineCount, { 17u }, { 32u } ) )
            {
                ++GetStatistics( EStatisticsId::eFunctionHPLength ).uiValue;
            }
            else if ( SRange::Contains( uiFunctionCodeLineCount, { 33u }, { 62u } ) )
            {
                ++GetStatistics( EStatisticsId::eFunction1PLength ).uiValue;
            }
            else if ( SRange::Contains( uiFunctionCodeLineCount, { 63u }, { 124u } ) )
            {
                ++GetStatistics( EStatisticsId::eFunction2PLength ).uiValue;
            }
            else if ( SRange::Contains( uiFunctionCodeLineCount, { 125u }, { 248u } ) )
            {
                ++GetStatistics( EStatisticsId::eFunction4PLength ).uiValue;
            }
            else if ( SRange::Contains( uiFunctionCodeLineCount, { 249u } ) )
            {
                ++GetStatistics( EStatisticsId::eFunction4PMoreLength ).uiValue;
            }
        }
    }
}

// ^^x
// std::size_t CFunctionLengthModule::SumStatisticsValues
// 3BGO JIRA-238 24-09-2020
std::size_t CFunctionLengthModule::SumStatisticsValues() const
{
    std::size_t uiTotalSum{ 0u };

    const std::vector<SStatisticsResult>& oResults = GetStatisticsResults();
    for ( const SStatisticsResult& oResult : oResults )
    {
        uiTotalSum += oResult.uiValue;
    }

    return uiTotalSum;
}

// ^^x
// void CFunctionLengthModule::ToPercent
// 3BGO JIRA-238 24-09-2020
void CFunctionLengthModule::ToPercent( std::size_t& uiStatisticsValue, const std::size_t uiTotalSumStatisticsValue )
{
    uiStatisticsValue = uiStatisticsValue * 100u / uiTotalSumStatisticsValue;
}
