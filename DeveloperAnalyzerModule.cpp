#include "DeveloperAnalyzerModule.h"

#include "SourceFile.h"
#include "StringHelper.h"

// ^^x
// CDeveloperAnalyzerModule::CDeveloperAnalyzerModule
// 3BGO JIRA-238 24-09-2020
CDeveloperAnalyzerModule::CDeveloperAnalyzerModule( std::string_view oDeveloperString ) :
    m_oDeveloperString{ oDeveloperString }
{
    CreateStatistics( "Function Length QP [0-16]" );
    CreateStatistics( "Function Length HP [17-32]" );
    CreateStatistics( "Function Length 1P [33-62]" );
    CreateStatistics( "Function Length 2P [63-124]" );
    CreateStatistics( "Function Length 4P [125-248]" );
    CreateStatistics( "Function Length 4P+ [249-more]" );
}

// ^^x
// void CDeveloperAnalyzerModule::ProcessHeaderFile
// 3BGO JIRA-238 24-09-2020
void CDeveloperAnalyzerModule::ProcessHeaderFile( const CHeaderFile& )
{

}

// ^^x
// void CDeveloperAnalyzerModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CDeveloperAnalyzerModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    const std::vector<SFindDataResult<CFunction>> oMemberFunctionVector = oSourceFile.GetMemberFunctions();

    for ( const SFindDataResult<CFunction>& oMemberFunction : oMemberFunctionVector )
    {
        if ( oMemberFunction.oData.GetInformation().has_value() )
        {
            if ( oMemberFunction.oData.GetInformation()->m_oAuthorString == m_oDeveloperString )
            {

            }
        }

        unsigned int uiFunctionCodeLineCount = CStringHelper::SplitLines( *oMemberFunction.oData.GetBody() ).size();

        if ( uiFunctionCodeLineCount >= 2u )
        {
            uiFunctionCodeLineCount -= 2u;

            if ( IsValueContainsInRange( uiFunctionCodeLineCount, 0u, 16u ) )
            {
                ++GetStatistics( 0u ).uiValue;
            }
            else if ( IsValueContainsInRange( uiFunctionCodeLineCount, 17u, 32u ) )
            {
                ++GetStatistics( 1u ).uiValue;
            }
            else if ( IsValueContainsInRange( uiFunctionCodeLineCount, 33u, 62u ) )
            {
                ++GetStatistics( 2u ).uiValue;
            }
            else if ( IsValueContainsInRange( uiFunctionCodeLineCount, 63u, 124u ) )
            {
                ++GetStatistics( 3u ).uiValue;
            }
            else if ( IsValueContainsInRange( uiFunctionCodeLineCount, 125u, 248u ) )
            {
                ++GetStatistics( 4u ).uiValue;
            }
            else if ( IsValueContainsInRange( uiFunctionCodeLineCount, 249u ) )
            {
                ++GetStatistics( 5u ).uiValue;
            }
        }
    }
}
