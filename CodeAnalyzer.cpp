#include "CodeAnalyzer.h"

CCodeAnalyzer::CCodeAnalyzer( const std::filesystem::path& oInputDirectoryPath ) :
    m_oInputDirectoryPath{ oInputDirectoryPath }
{

}

int CCodeAnalyzer::Execute()
{
    for ( std::unique_ptr<CStatisticsAnalyzerModule>& upoStatisticsAnalyzerModule : m_aStatisticsAnalyzerModules )
    {
        upoStatisticsAnalyzerModule->ProcessLine( "..." );
    }

    return EProgramStatusCodes::eSuccess;
}
