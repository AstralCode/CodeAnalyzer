#include "CodeAnalyzer.h"

#include <fstream>
#include <string>
#include <algorithm>

#include "ConsoleInterface.h"

// ^^x
// CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector CCodeAnalyzer::GetModules
// 3BGO JIRA-238 24-09-2020
CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector CCodeAnalyzer::GetModules() const
{
    ConstStatisticsAnalyzerModuleVector oStatisticsAnalyzerModules{};

    std::for_each( m_oStatisticsAnalyzerModuleVector.cbegin(), m_oStatisticsAnalyzerModuleVector.cend(), [&oStatisticsAnalyzerModules]( const std::unique_ptr<CStatisticsAnalyzerModule>& upoModule )
    {
        oStatisticsAnalyzerModules.emplace_back( std::cref( *upoModule ) );
    });

    return oStatisticsAnalyzerModules;
}

// ^^x
// EProgramStatusCodes CCodeAnalyzer::Execute
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CCodeAnalyzer::Execute( const std::filesystem::path& oInputDirectoryPath )
{
    EProgramStatusCodes eStatus = EProgramStatusCodes::eSuccess;

    const unsigned int uiProcessCodeFileCount = CountNumberCodeFiles( oInputDirectoryPath );

    std::string oFileContentString{};
    unsigned int uiProcessCodeFileNumber = 0u;

    std::filesystem::recursive_directory_iterator oDirectoryIterator{ oInputDirectoryPath };
    
    for ( const std::filesystem::path& oFilePath : oDirectoryIterator )
    {
        const CCodeFile::EType oFileType = AnalyzeCodeFileType( oFilePath );

        if ( oFileType != CCodeFile::EType::eUnknown )
        {
            ++uiProcessCodeFileNumber;

            eStatus = ReadFileContent( oFilePath, oFileContentString );

            if ( eStatus == EProgramStatusCodes::eSuccess )
            {
                for ( std::unique_ptr<CStatisticsAnalyzerModule>& upoStatisticsAnalyzerModule : m_oStatisticsAnalyzerModuleVector )
                {
                    const std::string oProcessCodeFileNumber = std::to_string( uiProcessCodeFileNumber );
                    const std::string oProcessCodeFileCount = std::to_string( uiProcessCodeFileCount );

                    CConsoleInterface::Print( "File(" + oProcessCodeFileNumber + "/" + oProcessCodeFileCount + "): " + oFilePath.string() );
                    
                    ProcessCodeFile( *upoStatisticsAnalyzerModule, oFilePath, oFileContentString, oFileType );
                }
            }
        }
    }

    return eStatus;
}

// ^^x
// CCodeFile::EType CCodeAnalyzer::AnalyzeCodeFileType
// 3BGO JIRA-238 24-09-2020
CCodeFile::EType CCodeAnalyzer::AnalyzeCodeFileType( const std::filesystem::path& oFilePath )
{
    CCodeFile::EType eType = CCodeFile::EType::eUnknown;

    if ( std::filesystem::is_regular_file( oFilePath ) && oFilePath.has_extension() )
    {
        if ( oFilePath.extension() == ".h" )
        {
            eType = CCodeFile::EType::eHeader;
        }

        if ( oFilePath.extension() == ".cpp" )
        {
            eType = CCodeFile::EType::eSource;
        }
    }

    return eType;
}

// ^^x
// void CCodeAnalyzer::ProcessCodeFile
// 3BGO JIRA-238 24-09-2020
void CCodeAnalyzer::ProcessCodeFile( CStatisticsAnalyzerModule& oAnalyzerModule, const std::filesystem::path& oPath, const std::string& oContentString, const CCodeFile::EType eType )
{
    CCodeFile oCodeFile{ oPath, oContentString, eType };

    oAnalyzerModule.PreProcessCodeFile( oCodeFile );
    oAnalyzerModule.ProcessCodeFile( oCodeFile );
    oAnalyzerModule.PostProcessCodeFile( oCodeFile );

    CConsoleInterface::ClearLine();
}

// ^^x
// EProgramStatusCodes CCodeAnalyzer::ReadFileContent
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CCodeAnalyzer::ReadFileContent( const std::filesystem::path& oFilePath, std::string& oFileContentString ) const
{
    EProgramStatusCodes eStatus = EProgramStatusCodes::eSuccess;

    std::ifstream oFileStream{ oFilePath.string(), std::fstream::in };

    if ( oFileStream.is_open() )
    {
        oFileContentString.assign( std::istreambuf_iterator<char>{ oFileStream }, std::istreambuf_iterator<char>{} );
    }
    else
    {
        eStatus = EProgramStatusCodes::eOpenInputFileError;
    }

    return eStatus;
}

// ^^x
// unsigned int CCodeAnalyzer::CountNumberCodeFiles
// 3BGO JIRA-238 24-09-2020
unsigned int CCodeAnalyzer::CountNumberCodeFiles( const std::filesystem::path& oDirectoryPath ) const
{
    return std::count_if( std::filesystem::recursive_directory_iterator{ oDirectoryPath },
                          std::filesystem::recursive_directory_iterator{},
                          [this]( const std::filesystem::path& oFilePath )
                          {
                              return AnalyzeCodeFileType( oFilePath ) != CCodeFile::EType::eUnknown;
                          } );
}
