#include "MemberFunctionCodeLineRangeModule.h"

#include "SourceFile.h"
#include "StringHelper.h"

// ^^x
// CMemberFunctionCodeLineRangeModule::CMemberFunctionCodeLineRangeModule
// 3BGO JIRA-239 30-09-2020
CMemberFunctionCodeLineRangeModule::CMemberFunctionCodeLineRangeModule()
{
    CreateStatistics( "Function Length QP [0-16]" );
    CreateStatistics( "Function Length HP [17-32]" );
    CreateStatistics( "Function Length 1P [33-62]" );
    CreateStatistics( "Function Length 2P [63-124]" );
    CreateStatistics( "Function Length 4P [125-248]" );
    CreateStatistics( "Function Length 4P+ [249-more]" );
}

// ^^x
// void CMemberFunctionCodeLineRangeModule::ProcessHeaderFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionCodeLineRangeModule::ProcessHeaderFile( const CHeaderFile& )
{

}

// ^^x
// void CMemberFunctionCodeLineRangeModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CMemberFunctionCodeLineRangeModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    const std::vector<SFindDataResult<CFunction>> oMemberFunctionVector = oSourceFile.GetMemberFunctions();

    for ( const SFindDataResult<CFunction>& oMemberFunction : oMemberFunctionVector )
    {
        unsigned int uiFunctionCodeLineCount = CStringHelper::SplitLines( *oMemberFunction.oData.GetBody() ).size();

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
