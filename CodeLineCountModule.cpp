#include "CodeLineCountModule.h"

#include <iostream>

#include "ProgramStatusCodes.h"

constexpr const char* MODULE_HEADER_STR = "CodeLineCount";

CCodeLineCountModule::CCodeLineCountModule() :
    m_uiStatisticsResult{ 0u }
{

}

int CCodeLineCountModule::ProcessLine( const std::string& oLine )
{
    std::cout << GetStatisticsHeader() << " -> " << oLine << std::endl;

    return EProgramStatusCodes::eSuccess;
}

std::string CCodeLineCountModule::GetStatisticsHeader() const
{
    return MODULE_HEADER_STR;
}

unsigned int CCodeLineCountModule::GetStatisticsResult() const
{
    return m_uiStatisticsResult;
}
