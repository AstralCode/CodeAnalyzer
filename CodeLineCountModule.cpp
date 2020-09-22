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
    std::cout << "CCodeLineCountModule::ProcessLine: " << oLine << std::endl;

    return EProgramStatusCodes::eSuccess;
}

void CCodeLineCountModule::OnStartProcess( const std::filesystem::path& oFilePath )
{
    std::cout << "CCodeLineCountModule::OnStartProcess: " << oFilePath.string() << std::endl;

    m_uiStatisticsResult = 0u;
}

void CCodeLineCountModule::OnEndProcess( const std::filesystem::path& oFilePath )
{
    std::cout << "CCodeLineCountModule::OnEndProcess: " << oFilePath.string() << std::endl;
}

std::string CCodeLineCountModule::GetStatisticsHeader() const
{
    return MODULE_HEADER_STR;
}

unsigned int CCodeLineCountModule::GetStatisticsResult() const
{
    return m_uiStatisticsResult;
}

bool CCodeLineCountModule::HasAcceptFileExtension( const std::filesystem::path& oFileExtensionPath ) const
{
    return oFileExtensionPath == ".cpp";
}
