#include "FunctionCountModule.h"

#include "SourceFile.h"
#include "StatisticsCollection.h"
#include "Utility.h"

// ^^x
// void CFunctionLengthModule::OnExcute
// 3BGO JIRA-238 23-10-2020
void CFunctionCountModule::OnExcute( CStatisticsCollection& oStatisticsCollection )
{
    oStatisticsCollection[EStatisticsTypes::eFunctionCount].oHeaderString = "Functions";
    oStatisticsCollection[EStatisticsTypes::eMemberFunctionCount].oHeaderString = "Member Functions";
    oStatisticsCollection[EStatisticsTypes::eMemberFunctionPercent].oHeaderString = "%";
    oStatisticsCollection[EStatisticsTypes::eGlobalFunctionCount].oHeaderString = "Global Functions";
    oStatisticsCollection[EStatisticsTypes::eGlobalFunctionPercent].oHeaderString = "%";
}

// ^^x
// void CFunctionCountModule::ProcessHeaderFile
// 3BGO JIRA-238 01-10-2020
void CFunctionCountModule::ProcessHeaderFile( const CHeaderFile&, CStatisticsCollection& )
{

}

// ^^x
// void CFunctionCountModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CFunctionCountModule::ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection )
{
    const std::size_t uiMemberFunctionCount = oSourceFile.GetMemberFunctions().size();
    const std::size_t uiGlobalFunctionCount = oSourceFile.GetGlobalFunctions().size();

    oStatisticsCollection[EStatisticsTypes::eFunctionCount].uiValue += ( uiMemberFunctionCount + uiGlobalFunctionCount );
    oStatisticsCollection[EStatisticsTypes::eMemberFunctionCount].uiValue += uiMemberFunctionCount;
    oStatisticsCollection[EStatisticsTypes::eGlobalFunctionCount].uiValue += uiGlobalFunctionCount;
}

// ^^x
// void CFunctionCountModule::OnExcuteComplete
// 3BGO JIRA-238 23-10-2020
void CFunctionCountModule::OnExcuteComplete( CStatisticsCollection& oStatisticsCollection )
{
    const std::size_t uiFunctionCount = oStatisticsCollection[EStatisticsTypes::eFunctionCount].uiValue;

    oStatisticsCollection[EStatisticsTypes::eMemberFunctionPercent].uiValue = ToPercent( oStatisticsCollection[EStatisticsTypes::eMemberFunctionCount].uiValue, uiFunctionCount );
    oStatisticsCollection[EStatisticsTypes::eGlobalFunctionPercent].uiValue = ToPercent( oStatisticsCollection[EStatisticsTypes::eGlobalFunctionCount].uiValue, uiFunctionCount );
}
