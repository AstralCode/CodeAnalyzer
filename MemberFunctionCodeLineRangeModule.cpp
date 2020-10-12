#include "MemberFunctionCodeLineRangeModule.h"

#include "SourceFile.h"
#include "StringHelper.h"

// ^^x
// CFunctionCodeLineRangeModule::CFunctionCodeLineRangeModule
// 3BGO JIRA-239 30-09-2020
CFunctionCodeLineRangeModule::CFunctionCodeLineRangeModule()
{
    CreateStatistics( "Function Length QP [0-16]" );
    CreateStatistics( "Function Length HP [17-32]" );
    CreateStatistics( "Function Length 1P [33-62]" );
    CreateStatistics( "Function Length 2P [63-124]" );
    CreateStatistics( "Function Length 4P [125-248]" );
    CreateStatistics( "Function Length 4P+ [249-more]" );
}

// ^^x
// void CFunctionCodeLineRangeModule::ProcessHeaderFile
// 3BGO JIRA-239 30-09-2020
void CFunctionCodeLineRangeModule::ProcessHeaderFile( const CHeaderFile& )
{

}

// ^^x
// void CFunctionCodeLineRangeModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CFunctionCodeLineRangeModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    CalculateStatistics( oSourceFile.GetGlobalFunctions() );
    CalculateStatistics( oSourceFile.GetMemberFunctions() );
}

// ^^x
// void CFunctionCodeLineRangeModule::CalculateStatistics
// 3BGO JIRA-238 24-09-2020
void CFunctionCodeLineRangeModule::CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector )
{
    for ( const SFindDataResult<CFunction>& oFunction : oFunctionVector )
    {
        unsigned int uiFunctionCodeLineCount = CStringHelper::SplitLines( *oFunction.oData.GetBody() ).size();

        if ( uiFunctionCodeLineCount >= 2u )
        {
            uiFunctionCodeLineCount -= 2u;

            if ( IsValueContainsInRange( uiFunctionCodeLineCount, 0u, 16u ) )
            {
                ++GetStatistics( EStatisticsId::eFunctionQPLength ).uiValue;
            }
            else if ( IsValueContainsInRange( uiFunctionCodeLineCount, 17u, 32u ) )
            {
                ++GetStatistics( EStatisticsId::eFunctionHPLength ).uiValue;
            }
            else if ( IsValueContainsInRange( uiFunctionCodeLineCount, 33u, 62u ) )
            {
                ++GetStatistics( EStatisticsId::eFunction1PLength ).uiValue;
            }
            else if ( IsValueContainsInRange( uiFunctionCodeLineCount, 63u, 124u ) )
            {
                ++GetStatistics( EStatisticsId::eFunction2PLength ).uiValue;
            }
            else if ( IsValueContainsInRange( uiFunctionCodeLineCount, 125u, 248u ) )
            {
                ++GetStatistics( EStatisticsId::eFunction4PLength ).uiValue;
            }
            else if ( IsValueContainsInRange( uiFunctionCodeLineCount, 249u ) )
            {
                ++GetStatistics( EStatisticsId::eFunction4PMoreLength ).uiValue;
            }
        }
    }
}
