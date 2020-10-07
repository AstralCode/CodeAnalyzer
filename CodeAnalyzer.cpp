#include "CodeAnalyzer.h"

#include <fstream>
#include <algorithm>

#include "ConsoleInterface.h"
#include "SourceFile.h"
#include "HeaderFile.h"

// ^^x
// CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector CCodeAnalyzer::GetAnalyzerModules
// 3BGO JIRA-238 24-09-2020
CCodeAnalyzer::ConstStatisticsAnalyzerModuleVector CCodeAnalyzer::GetAnalyzerModules() const
{
    ConstStatisticsAnalyzerModuleVector oAnalyzerModuleVector{};

    std::for_each( m_oAnalyzerModuleVector.cbegin(), m_oAnalyzerModuleVector.cend(), [&oAnalyzerModuleVector]( const std::unique_ptr<CStatisticsAnalyzerModule>& upoModule )
    {
        oAnalyzerModuleVector.emplace_back( std::cref( *upoModule ) );
    });

    return oAnalyzerModuleVector;
}

// ^^x
// EProgramStatusCodes CCodeAnalyzer::Execute
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CCodeAnalyzer::Execute( const SCommandLineArgumentDataset& oCommandLineArgumentDataset )
{
    EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

    CConsoleInterface::Print( "  Calculating the number of files. Please wait..." );
    const unsigned int uiProcessCodeFileCount = CountNumberCodeFiles( oCommandLineArgumentDataset.oInputDirectoryPath );
    CConsoleInterface::Print( "\r" );

    std::string oFileContentString{};
    unsigned int uiProcessCodeFileNumber{ 0u };

    std::filesystem::recursive_directory_iterator oDirectoryIterator{ oCommandLineArgumentDataset.oInputDirectoryPath };
    
    for ( const std::filesystem::path& oFilePath : oDirectoryIterator )
    {
        const ECodeFileType eFileType = CheckFileType( oFilePath );

        if ( eFileType != ECodeFileType::eUnknown )
        {
            ++uiProcessCodeFileNumber;

            PrintProgress( uiProcessCodeFileNumber, uiProcessCodeFileCount );

            eStatus = ReadFileContent( oFilePath, oFileContentString );

            if ( eStatus == EProgramStatusCodes::eSuccess )
            {
                PreProcessFileContent( oFileContentString );

                switch ( eFileType )
                {
                case ECodeFileType::eHeader:
                {
                    ProcessHeaderFile( oFilePath, oFileContentString );
                    break;
                }
                case ECodeFileType::eSource:
                {
                    ProcessSourceFile( oFilePath, oFileContentString );
                    break;
                }
                default:
                    break;
                }
            }
        }
    }

    return eStatus;
}

// ^^x
// ECodeFileType CCodeAnalyzer::CheckFileType
// 3BGO JIRA-238 24-09-2020
ECodeFileType CCodeAnalyzer::CheckFileType( const std::filesystem::path& oFilePath )
{
    ECodeFileType eType{ ECodeFileType::eUnknown };

    if ( std::filesystem::is_regular_file( oFilePath ) && oFilePath.has_extension() )
    {
        if ( oFilePath.extension() == ".h" )
        {
            eType = ECodeFileType::eHeader;
        }

        if ( oFilePath.extension() == ".cpp" )
        {
            eType = ECodeFileType::eSource;
        }
    }

    return eType;
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
// void CCodeAnalyzer::ProcessHeaderFile
// 3BGO JIRA-238 24-09-2020
void CCodeAnalyzer::ProcessHeaderFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString )
{
    CHeaderFile oHeaderFile{ oFilePath };
    oHeaderFile.SetCodeLineCount( m_oCodePareser.CountLines( oFileContentString ) );

    for ( std::unique_ptr<CStatisticsAnalyzerModule>& upoAnalyzerModule : m_oAnalyzerModuleVector )
    {
        upoAnalyzerModule->ProcessHeaderFile( oHeaderFile );
    }
}

// ^^x
// void CCodeAnalyzer::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CCodeAnalyzer::ProcessSourceFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString )
{
    CSourceFile oSourceFile{ oFilePath };
    oSourceFile.SetCodeLineCount( m_oCodePareser.CountLines( oFileContentString ) );
    oSourceFile.SetMemberFunctionDataset( m_oCodePareser.FindMemberFunctions( oFileContentString ) );

    for ( std::unique_ptr<CStatisticsAnalyzerModule>& upoAnalyzerModule : m_oAnalyzerModuleVector )
    {
        upoAnalyzerModule->ProcessSourceFile( oSourceFile );
    }
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

    CConsoleInterface::Print( "  Processing " + oProcessCodeFileNumber + "/" + oProcessCodeFileCount + " file " + oProgressBarString + " " + std::to_string( uiCurrentProgressPos ) + "%\r", CConsoleInterface::EForegroundColor::eGreen );
}

// ^^x
// bool CCodeAnalyzer::IsCodeFile
// 3BGO JIRA-238 06-10-2020
bool CCodeAnalyzer::IsCodeFile( const std::filesystem::path& oFilePath ) const
{
    return CheckFileType( oFilePath ) != ECodeFileType::eUnknown;
}
