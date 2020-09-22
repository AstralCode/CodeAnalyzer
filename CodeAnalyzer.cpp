#include "CodeAnalyzer.h"

CCodeAnalyzer::CCodeAnalyzer( const std::filesystem::path& oInputDirectoryPath ) :
    m_oInputDirectoryPath{ oInputDirectoryPath }
{

}

std::vector<std::reference_wrapper<const CStatisticsAnalyzerModule>> CCodeAnalyzer::GetModules() const
{
    std::vector<std::reference_wrapper<const CStatisticsAnalyzerModule>> oStatisticsAnalyzerModules{};

    std::for_each( m_aStatisticsAnalyzerModules.cbegin(), m_aStatisticsAnalyzerModules.cend(), [&oStatisticsAnalyzerModules]( const std::unique_ptr<CStatisticsAnalyzerModule>& upoModule )
    {
        oStatisticsAnalyzerModules.emplace_back( std::cref( *upoModule ) );
    });

    return oStatisticsAnalyzerModules;
}

int CCodeAnalyzer::Execute()
{
    for ( std::unique_ptr<CStatisticsAnalyzerModule>& upoStatisticsAnalyzerModule : m_aStatisticsAnalyzerModules )
    {
        upoStatisticsAnalyzerModule->ProcessLine( "..." );
    }

    return EProgramStatusCodes::eSuccess;
}
