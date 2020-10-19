#include "DeveloperAnalyzerModule.h"

#include "SourceFile.h"
#include "StringHelper.h"
#include "Utility.h"

// ^^x
// CDeveloperAnalyzerModule::CDeveloperAnalyzerModule
// 3BGO JIRA-238 24-09-2020
CDeveloperAnalyzerModule::CDeveloperAnalyzerModule( const std::string& oDeveloperString ) :
    m_oDeveloperString{ oDeveloperString }
{
    CreateStatistics( "Functions" );
    CreateStatistics( "Function Length QP" );
    CreateStatistics( "Function Length HP" );
    CreateStatistics( "Function Length 1P" );
    CreateStatistics( "Function Length 2P" );
    CreateStatistics( "Function Length 4P" );
    CreateStatistics( "Function Length 4P+" );
    CreateStatistics( "Functions Parse Error" );
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
            if ( oMemberFunction.oData.GetInformation()->oAuthorString == m_oDeveloperString )
            {
                ++GetStatistics( EStatisticsId::eFunctions ).uiValue;

                std::size_t uiFunctionCodeLineCount = CStringHelper::SplitLines( *oMemberFunction.oData.GetBody() ).size();

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
                else
                {
                    ++GetStatistics( EStatisticsId::eFunctionsParseError ).uiValue;
                }
            }
        }
    }
}
