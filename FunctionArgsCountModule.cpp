#include "FunctionArgsCountModule.h"

#include "SourceFile.h"
#include "StatisticsCollection.h"
#include "StringHelper.h"
#include "Utility.h"

// ^^x
// void CFunctionLengthModule::OnExcute
// 3BGO JIRA-238 22-10-2020
void CFunctionArgsCountModule::OnExcute( CStatisticsCollection& oStatisticsCollection )
{
    oStatisticsCollection[EStatisticsTypes::eFunction5PlusArgsCount].oHeaderString = "Functions Args 5+";
    oStatisticsCollection[EStatisticsTypes::eFunction5PlusArgsPercent].oHeaderString = "%";
}

// ^^x
// void CFunctionLengthModule::ProcessHeaderFile
// 3BGO JIRA-238 22-10-2020
void CFunctionArgsCountModule::ProcessHeaderFile( const CHeaderFile&, CStatisticsCollection& )
{

}

// ^^x
// void CFunctionLengthModule::ProcessSourceFile
// 3BGO JIRA-238 22-10-2020
void CFunctionArgsCountModule::ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection )
{
    CalculateStatistics( oSourceFile.GetGlobalFunctions(), oStatisticsCollection );
    CalculateStatistics( oSourceFile.GetMemberFunctions(), oStatisticsCollection );
}

// ^^x
// void CFunctionLengthModule::OnExcuteComplete
// 3BGO JIRA-238 22-10-2020
void CFunctionArgsCountModule::OnExcuteComplete( CStatisticsCollection& oStatisticsCollection )
{
    const std::size_t uiFunctionCount = oStatisticsCollection[EStatisticsTypes::eFunctionCount].uiValue;

    oStatisticsCollection[EStatisticsTypes::eFunction5PlusArgsPercent].uiValue = ToPercent( oStatisticsCollection[EStatisticsTypes::eFunction5PlusArgsCount].uiValue, uiFunctionCount );
}

// ^^x
// void CFunctionLengthModule::CalculateStatistics
// 3BGO JIRA-238 22-10-2020
void CFunctionArgsCountModule::CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector, CStatisticsCollection& oStatisticsCollection )
{
    for ( const SFindDataResult<CFunction>& oFunction : oFunctionVector )
    {
        if ( oFunction.oData.GetArgumentList().has_value() )
        {
            const std::size_t uiFunctionCodeLineCount = CStringHelper::Split( *oFunction.oData.GetArgumentList(), ',' ).size();

            if ( uiFunctionCodeLineCount > 5u )
            {
                ++oStatisticsCollection[EStatisticsTypes::eFunction5PlusArgsCount].uiValue;
            }
        }
    }
}
