#include "FunctionLengthModule.h"

#include <cmath>

#include "SourceFile.h"
#include "StatisticsCollection.h"
#include "StringHelper.h"
#include "Utility.h"

// ^^x
// void CFunctionLengthModule::OnExcute
// 3BGO JIRA-238 30-09-2020
void CFunctionLengthModule::OnExcute( CStatisticsCollection& oStatisticsCollection )
{
    oStatisticsCollection[EStatisticsTypes::eFunctionLengthQPCount].oHeaderString = "Functions QP";
    oStatisticsCollection[EStatisticsTypes::eFunctionLengthQPPercent].oHeaderString = "%";
    oStatisticsCollection[EStatisticsTypes::eFunctionLengthHPCount].oHeaderString = "Functions HP";
    oStatisticsCollection[EStatisticsTypes::eFunctionLengthHPPercent].oHeaderString = "%";
    oStatisticsCollection[EStatisticsTypes::eFunctionLength1PCount].oHeaderString = "Functions 1P";
    oStatisticsCollection[EStatisticsTypes::eFunctionLength1PPercent].oHeaderString = "%";
    oStatisticsCollection[EStatisticsTypes::eFunctionLength2PCount].oHeaderString = "Functions 2P";
    oStatisticsCollection[EStatisticsTypes::eFunctionLength2PPercent].oHeaderString = "%";
    oStatisticsCollection[EStatisticsTypes::eFunctionLength4PCount].oHeaderString = "Functions 4P";
    oStatisticsCollection[EStatisticsTypes::eFunctionLength4PPercent].oHeaderString = "%";
    oStatisticsCollection[EStatisticsTypes::eFunctionLength4PPlusCount].oHeaderString = "Functions 4P+";
    oStatisticsCollection[EStatisticsTypes::eFunctionLength4PPlusPercent].oHeaderString = "%";
}

// ^^x
// void CFunctionLengthModule::ProcessHeaderFile
// 3BGO JIRA-238 30-09-2020
void CFunctionLengthModule::ProcessHeaderFile( const CHeaderFile&, CStatisticsCollection& )
{

}

// ^^x
// void CFunctionLengthModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CFunctionLengthModule::ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection )
{
    CalculateStatistics( oSourceFile.GetGlobalFunctions(), oStatisticsCollection );
    CalculateStatistics( oSourceFile.GetMemberFunctions(), oStatisticsCollection );
}

// ^^x
// void CFunctionLengthModule::OnExcuteComplete
// 3BGO JIRA-238 30-09-2020
void CFunctionLengthModule::OnExcuteComplete( CStatisticsCollection& oStatisticsCollection )
{
    const std::size_t uiFunctionCount = oStatisticsCollection[EStatisticsTypes::eFunctionCount].uiValue;

    oStatisticsCollection[EStatisticsTypes::eFunctionLengthQPPercent].uiValue = ToPercent( oStatisticsCollection[EStatisticsTypes::eFunctionLengthQPCount].uiValue, uiFunctionCount );
    oStatisticsCollection[EStatisticsTypes::eFunctionLengthHPPercent].uiValue = ToPercent( oStatisticsCollection[EStatisticsTypes::eFunctionLengthHPCount].uiValue, uiFunctionCount );
    oStatisticsCollection[EStatisticsTypes::eFunctionLength1PPercent].uiValue = ToPercent( oStatisticsCollection[EStatisticsTypes::eFunctionLength1PCount].uiValue, uiFunctionCount );
    oStatisticsCollection[EStatisticsTypes::eFunctionLength2PPercent].uiValue = ToPercent( oStatisticsCollection[EStatisticsTypes::eFunctionLength2PCount].uiValue, uiFunctionCount );
    oStatisticsCollection[EStatisticsTypes::eFunctionLength4PPercent].uiValue = ToPercent( oStatisticsCollection[EStatisticsTypes::eFunctionLength4PCount].uiValue, uiFunctionCount );
    oStatisticsCollection[EStatisticsTypes::eFunctionLength4PPlusPercent].uiValue = ToPercent( oStatisticsCollection[EStatisticsTypes::eFunctionLength4PPlusCount].uiValue, uiFunctionCount );
}

// ^^x
// void CFunctionLengthModule::CalculateStatistics
// 3BGO JIRA-238 24-09-2020
void CFunctionLengthModule::CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector, CStatisticsCollection& oStatisticsCollection )
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
                ++oStatisticsCollection[EStatisticsTypes::eFunctionLengthQPCount].uiValue;
            }
            else if ( SRange::Contains( uiFunctionCodeLineCount, { 17u }, { 32u } ) )
            {
                ++oStatisticsCollection[EStatisticsTypes::eFunctionLengthHPCount].uiValue;
            }
            else if ( SRange::Contains( uiFunctionCodeLineCount, { 33u }, { 62u } ) )
            {
                ++oStatisticsCollection[EStatisticsTypes::eFunctionLength1PCount].uiValue;
            }
            else if ( SRange::Contains( uiFunctionCodeLineCount, { 63u }, { 124u } ) )
            {
                ++oStatisticsCollection[EStatisticsTypes::eFunctionLength2PCount].uiValue;
            }
            else if ( SRange::Contains( uiFunctionCodeLineCount, { 125u }, { 248u } ) )
            {
                ++oStatisticsCollection[EStatisticsTypes::eFunctionLength4PCount].uiValue;
            }
            else if ( SRange::Contains( uiFunctionCodeLineCount, { 249u } ) )
            {
                ++oStatisticsCollection[EStatisticsTypes::eFunctionLength4PPlusCount].uiValue;
            }
        }
    }
}
