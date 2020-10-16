#include "FunctionLengthModule.h"

#include "SourceFile.h"
#include "StringHelper.h"
#include "Utility.h"

// ^^x
// CFunctionLengthModule::CFunctionLengthModule
// 3BGO JIRA-239 30-09-2020
CFunctionLengthModule::CFunctionLengthModule()
{
    CreateStatistics( "Function Length QP [0-16]" );
    CreateStatistics( "Function Length HP [17-32]" );
    CreateStatistics( "Function Length 1P [33-62]" );
    CreateStatistics( "Function Length 2P [63-124]" );
    CreateStatistics( "Function Length 4P [125-248]" );
    CreateStatistics( "Function Length 4P+ [249-more]" );
}

// ^^x
// void CFunctionLengthModule::ProcessHeaderFile
// 3BGO JIRA-239 30-09-2020
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
// void CFunctionLengthModule::CalculateStatistics
// 3BGO JIRA-238 24-09-2020
void CFunctionLengthModule::CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector )
{
    for ( const SFindDataResult<CFunction>& oFunction : oFunctionVector )
    {
        std::size_t uiFunctionCodeLineCount = CStringHelper::SplitLines( *oFunction.oData.GetBody() ).size();

        if ( uiFunctionCodeLineCount >= 2u )
        {
            uiFunctionCodeLineCount -= 2u;

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
