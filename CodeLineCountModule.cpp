#include "CodeLineCountModule.h"

#include "HeaderFile.h"
#include "SourceFile.h"
#include "StatisticsCollection.h"

// ^^x
// void CCodeLineCountModule::OnPreExecute
// 3BGO JIRA-238 24-09-2020
void CCodeLineCountModule::OnPreExecute( CStatisticsCollection& oStatisticsCollection )
{
    oStatisticsCollection[EStatisticsTypes::eCodeLineCount].oHeaderString = "Code Lines";
}

// ^^x
// void CCodeLineCountModule::ProcessHeaderFile
// 3BGO JIRA-238 24-09-2020
void CCodeLineCountModule::ProcessHeaderFile( const CHeaderFile& oHeaderFile, CStatisticsCollection& oStatisticsCollection )
{
    oStatisticsCollection[EStatisticsTypes::eCodeLineCount].uiValue += oHeaderFile.GetCodeLineCount();
}

// ^^x
// void CCodeLineCountModule::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CCodeLineCountModule::ProcessSourceFile( const CSourceFile& oSourceFile, CStatisticsCollection& oStatisticsCollection )
{
    oStatisticsCollection[EStatisticsTypes::eCodeLineCount].uiValue += oSourceFile.GetCodeLineCount();
}

// ^^x
// void CCodeLineCountModule::OnPostExecute
// 3BGO JIRA-238 24-09-2020
void CCodeLineCountModule::OnPostExecute( CStatisticsCollection& )
{

}
