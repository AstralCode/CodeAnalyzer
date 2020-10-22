#include "FunctionArgsCountModule.h"

#include "SourceFile.h"
#include "StringHelper.h"

// ^^x
// CFunctionArgsCountModule::CFunctionArgsCountModule
// 3BGO JIRA-238 22-10-2020
CFunctionArgsCountModule::CFunctionArgsCountModule()
{
    CreateStatistics( "Functions Args 5+" );
}

// ^^x
// void CFunctionLengthModule::ProcessHeaderFile
// 3BGO JIRA-238 22-10-2020
void CFunctionArgsCountModule::ProcessHeaderFile( const CHeaderFile& )
{

}

// ^^x
// void CFunctionLengthModule::ProcessSourceFile
// 3BGO JIRA-238 22-10-2020
void CFunctionArgsCountModule::ProcessSourceFile( const CSourceFile& oSourceFile )
{
    CalculateStatistics( oSourceFile.GetGlobalFunctions() );
    CalculateStatistics( oSourceFile.GetMemberFunctions() );
}

// ^^x
// void CFunctionLengthModule::ProcessSourceFile
// 3BGO JIRA-238 22-10-2020
void CFunctionArgsCountModule::CalculateStatistics( const std::vector<SFindDataResult<CFunction>>& oFunctionVector )
{
    for ( const SFindDataResult<CFunction>& oFunction : oFunctionVector )
    {
        if ( oFunction.oData.GetArgumentList().has_value() )
        {
            const std::size_t uiFunctionCodeLineCount = CStringHelper::Split( *oFunction.oData.GetArgumentList(), ',' ).size();

            if ( uiFunctionCodeLineCount > 5u )
            {
                ++GetStatistics( EStatisticsId::eFunctionArgs5MoreCount ).uiValue;
            }
        }
    }
}
