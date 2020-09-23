#include "CodeAnalyzer.h"

#include <fstream>
#include <string>

CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector CCodeAnalyzer::GetModules() const
{
    ConstStatisticsAnalyzerModuleVector oStatisticsAnalyzerModules{};

    std::for_each( m_aStatisticsAnalyzerModules.cbegin(), m_aStatisticsAnalyzerModules.cend(), [&oStatisticsAnalyzerModules]( const std::unique_ptr<CStatisticsAnalyzerModule>& upoModule )
    {
        oStatisticsAnalyzerModules.emplace_back( std::cref( *upoModule ) );
    });

    return oStatisticsAnalyzerModules;
}

int CCodeAnalyzer::Execute( const std::filesystem::path& oInputDirectoryPath ) const
{
    int iProgramStatusCode = static_cast<int>( EProgramStatusCodes::eSuccess);

    std::filesystem::recursive_directory_iterator oDirectoryIterator{ oInputDirectoryPath };
    std::string oFileLineString;

    for ( const std::filesystem::path& oFilePath : oDirectoryIterator )
    {
        if ( !std::filesystem::is_directory( oFilePath ) )
        {
            if ( oFilePath.filename().has_extension() )
            {
                const StatisticsAnalyzerModuleVector aStatisticsAnalyzerModules = GetModules( oFilePath.filename().extension() );
   
                std::ifstream oFileStream{ oFilePath.string(), std::fstream::in };

                if ( oFileStream.is_open() )
                {
                    for ( const StatisticsAnalyzerModule& oStatisticsAnalyzerModule : aStatisticsAnalyzerModules )
                    {
                        oStatisticsAnalyzerModule.get().OnStartProcess( oFilePath );
                    }

                    while ( std::getline( oFileStream, oFileLineString ) )
                    {
                        for ( const StatisticsAnalyzerModule& oStatisticsAnalyzerModule : aStatisticsAnalyzerModules )
                        {
                            oStatisticsAnalyzerModule.get().ProcessLine( oFileLineString );
                        }
                    }

                    for ( const StatisticsAnalyzerModule& oStatisticsAnalyzerModule : aStatisticsAnalyzerModules )
                    {
                        oStatisticsAnalyzerModule.get().OnEndProcess( oFilePath );
                    }

                    oFileStream.close();
                }
                else
                {
                    iProgramStatusCode = static_cast<int>( EProgramStatusCodes::eOpenInputFileError );
                }
            }
        }
    }

    return iProgramStatusCode;
}

CCodeAnalyzer::StatisticsAnalyzerModuleVector CCodeAnalyzer::GetModules( const std::filesystem::path& oAcceptedFileExtensionPath ) const
{
    CCodeAnalyzer::StatisticsAnalyzerModuleVector oStatisticsAnalyzerModules{};

    std::for_each( m_aStatisticsAnalyzerModules.cbegin(), m_aStatisticsAnalyzerModules.cend(), [&oStatisticsAnalyzerModules, oAcceptedFileExtensionPath]( const std::unique_ptr<CStatisticsAnalyzerModule>& upoModule )
    {
        if ( upoModule->HasAcceptFileExtension( oAcceptedFileExtensionPath ) )
        {
            oStatisticsAnalyzerModules.emplace_back( std::ref( *upoModule ) );
        }
    });

    return oStatisticsAnalyzerModules;
}
