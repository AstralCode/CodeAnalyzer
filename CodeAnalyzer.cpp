#include "CodeAnalyzer.h"

#include <fstream>
#include <algorithm>

#include "ConsoleInterface.h"
#include "CodeFile.h"

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
    EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

    CConsoleInterface::Print( "  Calculating the number of files. Please wait..." );
    const unsigned int uiProcessCodeFileCount = CountNumberCodeFiles( oInputDirectoryPath );
    CConsoleInterface::Print( "\r" );
/*
    CConsoleInterface::Print( "  Calculating the size of files. Please wait..." );
    const std::uintmax_t uiProcessCodeFilesSize = CountSizeCodeFiles( oInputDirectoryPath );
    CConsoleInterface::Print( "\r" );
*/
    std::string oFileContentString{};
    unsigned int uiProcessCodeFileNumber{ 0u };

    std::filesystem::recursive_directory_iterator oDirectoryIterator{ oInputDirectoryPath };
    
    for ( const std::filesystem::path& oFilePath : oDirectoryIterator )
    {
        const CCodeFile::EType oFileType = AnalyzeFileType( oFilePath );

        if ( oFileType != CCodeFile::EType::eUnknown )
        {
            ++uiProcessCodeFileNumber;

            PrintProgress( uiProcessCodeFileNumber, uiProcessCodeFileCount );

            eStatus = ReadFileContent( oFilePath, oFileContentString );

            if ( eStatus == EProgramStatusCodes::eSuccess )
            {
                PreProcessFileContent( oFileContentString );

                CCodeFile oCodeFile{ oFilePath, oFileContentString, oFileType };

                if ( oFileType == CCodeFile::EType::eSource )
                {
                    oCodeFile.SetMemberFunctionDataset( m_oCodePareser.FindMemberFunctions( oCodeFile.GetCode() ) );
                }

                for ( std::unique_ptr<CStatisticsAnalyzerModule>& upoStatisticsAnalyzerModule : m_oStatisticsAnalyzerModuleVector )
                {
                    ProcessCodeFile( *upoStatisticsAnalyzerModule, oCodeFile );
                }
            }
        }
    }

    return eStatus;
}

// ^^x
// CCodeFile::EType CCodeAnalyzer::AnalyzeFileType
// 3BGO JIRA-238 24-09-2020
CCodeFile::EType CCodeAnalyzer::AnalyzeFileType( const std::filesystem::path& oFilePath )
{
    CCodeFile::EType eType{ CCodeFile::EType::eUnknown };

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
void CCodeAnalyzer::ProcessCodeFile( CStatisticsAnalyzerModule& oAnalyzerModule, const CCodeFile& oCodeFile ) const
{
    oAnalyzerModule.PreProcessCodeFile( oCodeFile );
    oAnalyzerModule.ProcessCodeFile( oCodeFile );
    oAnalyzerModule.PostProcessCodeFile( oCodeFile );
}

// ^^x
// EProgramStatusCodes CCodeAnalyzer::ReadFileContent
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CCodeAnalyzer::ReadFileContent( const std::filesystem::path& oFilePath, std::string& oFileContentString ) const
{
    EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

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
// void CCodeAnalyzer::PreProcessFileContent
// 3BGO JIRA-238 24-09-2020
void CCodeAnalyzer::PreProcessFileContent( std::string& oFileContentString ) const
{
    oFileContentString = m_oCodePareser.RemoveMultilineComments( oFileContentString );
}

// ^^x
// unsigned int CCodeAnalyzer::CountNumberCodeFiles
// 3BGO JIRA-238 24-09-2020
unsigned int CCodeAnalyzer::CountNumberCodeFiles( const std::filesystem::path& oDirectoryPath ) const
{
    return std::count_if( std::filesystem::recursive_directory_iterator{ oDirectoryPath },
                          std::filesystem::recursive_directory_iterator{},
                          [this]( const std::filesystem::path& oFilePath ) { return IsCodeFile( oFilePath ); } );
}

// ^^x
// std::uintmax_t CCodeAnalyzer::CountSizeCodeFiles
// 3BGO JIRA-238 24-09-2020
std::uintmax_t CCodeAnalyzer::CountSizeCodeFiles( const std::filesystem::path& oDirectoryPath ) const
{
    std::uintmax_t ullFileCodeSizes = 0u;

    std::filesystem::recursive_directory_iterator oDirectoryIterator{ oDirectoryPath };

    for ( const std::filesystem::path& oFilePath : oDirectoryIterator )
    {
        if ( IsCodeFile( oFilePath ) )
        {
            ullFileCodeSizes += std::filesystem::file_size( oFilePath );
        }
    }

    return ullFileCodeSizes;
}

// ^^x
// void CCodeAnalyzer::PrintProgress
// 3BGO JIRA-238 24-09-2020
void CCodeAnalyzer::PrintProgress( const unsigned int uiFileNumber, const unsigned int uiFileCount ) const
{
    const unsigned int uiCurrentProgressPos = uiFileNumber * 100u / uiFileCount;
    const std::string oCompleteProgressString( uiCurrentProgressPos / 2u, static_cast<char>( 219 ) );

    std::string oProgressBarString( 50u, static_cast<char>( 176 ) );
    oProgressBarString.replace( 0u, uiCurrentProgressPos / 2u, oCompleteProgressString );

    const std::string oProcessCodeFileNumber = std::to_string( uiFileNumber );
    const std::string oProcessCodeFileCount = std::to_string( uiFileCount );

    CConsoleInterface::Print( "  Processing " + oProcessCodeFileNumber + "/" + oProcessCodeFileCount + " file | " + oProgressBarString + " " + std::to_string( uiCurrentProgressPos ) + "%\r" );
    CConsoleInterface::Flush();
}

bool CCodeAnalyzer::IsCodeFile( const std::filesystem::path& oFilePath ) const
{
    return AnalyzeFileType( oFilePath ) != CCodeFile::EType::eUnknown;
}
