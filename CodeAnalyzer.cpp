#include "CodeAnalyzer.h"

#include <fstream>
#include <string>

#include "HeaderCodeFile.h"
#include "SourceCodeFile.h"
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

    std::string oFileContentString{};

    std::filesystem::recursive_directory_iterator oDirectoryIterator{ oInputDirectoryPath };
    
    for ( const std::filesystem::path& oFilePath : oDirectoryIterator )
    {
        if ( !std::filesystem::is_directory( oFilePath ) )
        {
            const CCodeFile::EType oFileType = CCodeFile::CheckFileExtension( oFilePath );

            if ( oFileType != CCodeFile::EType::eUnknown )
            {
                eStatus = ReadFileContent( oFilePath, oFileContentString );

                if ( eStatus == EProgramStatusCodes::eSuccess )
                {
                    ProcessFile( oFilePath, oFileContentString, oFileType );
                }
            }
        }
    }

    return eStatus;
}

// ^^x
// void CCodeAnalyzer::ProcessFile
// 3BGO JIRA-238 24-09-2020
void CCodeAnalyzer::ProcessFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString, const CCodeFile::EType oFileCodeType )
{
    for ( std::unique_ptr<CStatisticsAnalyzerModule>& upoStatisticsAnalyzerModule : m_oStatisticsAnalyzerModuleVector )
    {
        CConsoleInterface::Print( "Process \"" + upoStatisticsAnalyzerModule->GetModuleName() + "\" module | " + oFilePath.string() );

        if ( oFileCodeType == CCodeFile::EType::eHeader )
        {
            CHeaderCodeFile oHeaderCodeFile{ oFilePath, oFileContentString };
            upoStatisticsAnalyzerModule->OnStartProcessFile( oHeaderCodeFile );
            upoStatisticsAnalyzerModule->ProcessHeaderFile( oHeaderCodeFile );
            upoStatisticsAnalyzerModule->OnEndProcessFile( oHeaderCodeFile );
        }

        if ( oFileCodeType == CCodeFile::EType::eSource )
        {
            CSourceCodeFile oSourceCodeFile{ oFilePath, oFileContentString };
            upoStatisticsAnalyzerModule->OnStartProcessFile( oSourceCodeFile );
            upoStatisticsAnalyzerModule->ProcessSourceFile( oSourceCodeFile );
            upoStatisticsAnalyzerModule->OnEndProcessFile( oSourceCodeFile );
        }

        CConsoleInterface::ClearLine();
    }
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
        oFileContentString.assign( std::istreambuf_iterator<char>{oFileStream}, std::istreambuf_iterator<char>{} );
    }
    else
    {
        eStatus = EProgramStatusCodes::eOpenInputFileError;
    }

    return eStatus;
}
