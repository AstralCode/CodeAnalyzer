#include "MemberFunctionCodeLineRangeModule.h"

#include "StringHelper.h"

// ^^x
// CMemberFunctionCodeLineRangeModule::CMemberFunctionCodeLineRangeModule
// 3BGO JIRA-239 30-09-2020
CMemberFunctionCodeLineRangeModule::CMemberFunctionCodeLineRangeModule( CCodeParser& oCodeParser ) :
    CStatisticsAnalyzerModule{ oCodeParser }
{
    CreateStatistics( "Function Code Line Range[0-20]" );
    CreateStatistics( "Function Code Line Range[21-50]" );
    CreateStatistics( "Function Code Line Range[51-100]" );
    CreateStatistics( "Function Code Line Range[101-300]" );
    CreateStatistics( "Function Code Line Range[301-500]" );
    CreateStatistics( "Function Code Line Range[501-more]" );
}

// ^^x
// void CMemberFunctionCodeLineRangeModule::PreProcessCodeFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionCodeLineRangeModule::PreProcessCodeFile( const CCodeFile& )
{

}

// ^^x
// void CMemberFunctionCodeLineRangeModule::ProcessCodeFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionCodeLineRangeModule::ProcessCodeFile( const CCodeFile& oCodeFile )
{
    if ( oCodeFile.GetType() == CCodeFile::EType::eSource )
    {
        const std::vector<SMemberFunctionHeaderDataset> oFunctionDatasetVector = oCodeFile.GetMemberFunctionDataset();

        for ( const SMemberFunctionHeaderDataset& oFunctionDataset : oFunctionDatasetVector )
        {
            unsigned int uiFunctionCodeLineCount = CStringHelper::SplitLines( oFunctionDataset.oBodyString ).size();

            if ( uiFunctionCodeLineCount > 2u )
            {
                uiFunctionCodeLineCount -= 2u;

                if ( IsValueContainsInRange( uiFunctionCodeLineCount, 0u, 20u ) )
                {
                    ++GetStatistics( 0u ).uiValue;
                }
                else if ( IsValueContainsInRange( uiFunctionCodeLineCount, 21u, 50u ) )
                {
                    ++GetStatistics( 1u ).uiValue;
                }
                else if ( IsValueContainsInRange( uiFunctionCodeLineCount, 51u, 100u ) )
                {
                    ++GetStatistics( 2u ).uiValue;
                }
                else if ( IsValueContainsInRange( uiFunctionCodeLineCount, 101u, 300u ) )
                {
                    ++GetStatistics( 3u ).uiValue;
                }
                else if ( IsValueContainsInRange( uiFunctionCodeLineCount, 301u, 500u ) )
                {
                    ++GetStatistics( 4u ).uiValue;
                }
                else if ( IsValueContainsInRange( uiFunctionCodeLineCount, 501u ) )
                {
                    ++GetStatistics( 5u ).uiValue;
                }
            }
        }
    }
}

// ^^x
// void CMemberFunctionCodeLineRangeModule::PostProcessCodeFile
// 3BGO JIRA-239 30-09-2020
void CMemberFunctionCodeLineRangeModule::PostProcessCodeFile( const CCodeFile& )
{

}

// ^^x
// std::string CMemberFunctionCodeLineRangeModule::GetModuleName
// 3BGO JIRA-238 01-10-2020
std::string CMemberFunctionCodeLineRangeModule::GetModuleName() const
{
    return "Function Line Range";
}
