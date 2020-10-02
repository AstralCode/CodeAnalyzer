#include "MemberFunctionCodeLineRangeModule.h"

#include "CodeParser.h"
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
    CreateStatistics( "Function Code Line Range[301-more]" );
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
        const std::vector<SFindMemberFunctionDetailResult> oFunctionResultVector = m_oCodeParser.FindMemberFunctionsDetails( oCodeFile );

        for ( const SFindMemberFunctionDetailResult& oFunctionResult : oFunctionResultVector )
        {
            unsigned int uiFunctionCodeLineCount = CStringHelper::SplitLines( oFunctionResult.oBodyDataset.oBodyString ).size();

            if ( uiFunctionCodeLineCount > 2u )
            {
                uiFunctionCodeLineCount -= 2u;

                if ( uiFunctionCodeLineCount == std::clamp( uiFunctionCodeLineCount, 0u, 20u ) )
                {
                    ++GetStatistics( 0u ).uiValue;
                }
                else if ( uiFunctionCodeLineCount == std::clamp( uiFunctionCodeLineCount, 21u, 50u ) )
                {
                    ++GetStatistics( 1u ).uiValue;
                }
                else if ( uiFunctionCodeLineCount == std::clamp( uiFunctionCodeLineCount, 51u, 100u ) )
                {
                    ++GetStatistics( 2u ).uiValue;
                }
                else if ( uiFunctionCodeLineCount == std::clamp( uiFunctionCodeLineCount, 101u, 300u ) )
                {
                    ++GetStatistics( 3u ).uiValue;
                }
                else if ( uiFunctionCodeLineCount == std::clamp( uiFunctionCodeLineCount, 301u, std::numeric_limits<unsigned int>::max() ) )
                {
                    ++GetStatistics( 4u ).uiValue;
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
