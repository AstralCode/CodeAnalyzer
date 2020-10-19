#include "CodeAnalyzer.h"

#include <fstream>
#include <algorithm>

#include "ConsoleInterface.h"
#include "SourceFile.h"
#include "HeaderFile.h"

// ^^x
// std::vector<SStatisticsResult> CCodeAnalyzer::GetStatisticsResults
// 3BGO JIRA-238 24-09-2020
std::vector<SStatisticsResult> CCodeAnalyzer::GetStatisticsResults() const
{
    std::vector<SStatisticsResult> oStatisticsResultVector{};

    for ( const std::unique_ptr<CCodeAnalyzerModule>& upoAnalyzerModule : m_oAnalyzerModuleVector )
    {
        const std::vector<SStatisticsResult> oAnalyzerModuleResults = upoAnalyzerModule->GetStatisticsResults();
        oStatisticsResultVector.insert( oStatisticsResultVector.end(), oAnalyzerModuleResults.cbegin(), oAnalyzerModuleResults.cend() );
    }

    return oStatisticsResultVector;
}

// ^^x
// EProgramStatusCodes CCodeAnalyzer::Execute
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CCodeAnalyzer::Execute( const std::filesystem::path& oInputDirectoryPath, std::optional<std::string> oDeveloperString )
{
    EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

    CConsoleInterface::PrintLineTime( "Code analysis in progress..." );
    CConsoleInterface::Print( "  Calculating the number of files. Please wait...\r" );
   
    std::string oFileContentString{};
    unsigned int uiProcessCodeFileNumber{ 0u };

    const std::size_t uiProcessCodeFileCount = CountNumberCodeFiles( oInputDirectoryPath );
    std::filesystem::recursive_directory_iterator oDirectoryIterator{ oInputDirectoryPath };

    for ( const std::filesystem::path& oFilePath : oDirectoryIterator )
    {
        const ECodeFileType eFileType = CheckFileType( oFilePath );

        if ( eFileType != ECodeFileType::eUnknown )
        {
           PrintProgress( ++uiProcessCodeFileNumber, uiProcessCodeFileCount );

            eStatus = ReadFileContent( oFilePath, oFileContentString );

            if ( eStatus == EProgramStatusCodes::eSuccess )
            {
                PreProcessFileContent( oFileContentString );

                switch ( eFileType )
                {
                case ECodeFileType::eHeader:
                {
                    ProcessHeaderFile( oFilePath, oFileContentString, oDeveloperString );
                    break;
                }
                case ECodeFileType::eSource:
                {
                    ProcessSourceFile( oFilePath, oFileContentString, oDeveloperString );
                    break;
                }
                case ECodeFileType::eUnknown:
                default:
                    break;
                }
            }
        }
    }

    if ( eStatus == EProgramStatusCodes::eSuccess )
    {
        CConsoleInterface::ClearLine();
        CConsoleInterface::PrintLineTime( "Analysis complete!" );
    }

    return eStatus;
}

// ^^x
// std::size_t CCodeAnalyzer::CountNumberCodeFiles
// 3BGO JIRA-238 24-09-2020
std::size_t CCodeAnalyzer::CountNumberCodeFiles( const std::filesystem::path& oDirectoryPath )
{
    return std::count_if( std::filesystem::recursive_directory_iterator{ oDirectoryPath },
                          std::filesystem::recursive_directory_iterator{},
                          []( const std::filesystem::path& oFilePath ) { return IsCodeFile( oFilePath ); } );
}

// ^^x
// std::uintmax_t CCodeAnalyzer::CountSizeCodeFiles
// 3BGO JIRA-238 24-09-2020
std::uintmax_t CCodeAnalyzer::CountSizeCodeFiles( const std::filesystem::path& oDirectoryPath )
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
// ECodeFileType CCodeAnalyzer::CheckFileType
// 3BGO JIRA-238 24-09-2020
ECodeFileType CCodeAnalyzer::CheckFileType( const std::filesystem::path& oFilePath )
{
    ECodeFileType eType{ ECodeFileType::eUnknown };

    if ( std::filesystem::is_regular_file( oFilePath ) )
    {
        if ( oFilePath.has_extension() )
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
    }

    return eType;
}

// ^^x
// bool CCodeAnalyzer::IsCodeFile
// 3BGO JIRA-238 06-10-2020
bool CCodeAnalyzer::IsCodeFile( const std::filesystem::path& oFilePath )
{
    return CheckFileType( oFilePath ) != ECodeFileType::eUnknown;
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
    m_oCodePareser.RemoveMultiLineComments( oFileContentString );
    m_oCodePareser.RemoveDirectives( oFileContentString );
    m_oCodePareser.RemoveMacros( oFileContentString );
    m_oCodePareser.RemoveStatemets( oFileContentString );
    m_oCodePareser.RemoveMemberDataListInitialization( oFileContentString );
}

// ^^x
// void CCodeAnalyzer::ProcessHeaderFile
// 3BGO JIRA-238 24-09-2020
void CCodeAnalyzer::ProcessHeaderFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString, std::optional<std::string> oDeveloperString )
{
    CHeaderFile oHeaderFile{ oFilePath };
    oHeaderFile.SetCodeLineCount( m_oCodePareser.CountLines( oFileContentString ) );

    for ( std::unique_ptr<CCodeAnalyzerModule>& upoAnalyzerModule : m_oAnalyzerModuleVector )
    {
        upoAnalyzerModule->ProcessHeaderFile( oHeaderFile );
    }
}

// ^^x
// void CCodeAnalyzer::ProcessSourceFile
// 3BGO JIRA-238 24-09-2020
void CCodeAnalyzer::ProcessSourceFile( const std::filesystem::path& oFilePath, const std::string& oFileContentString, std::optional<std::string> oDeveloperString )
{
    CSourceFile oSourceFile{ oFilePath };
    oSourceFile.SetCodeLineCount( m_oCodePareser.CountLines( oFileContentString ) );
    oSourceFile.SetGlobalVariables( m_oCodePareser.FindGlobalVariables( oFileContentString ) );

    std::vector<SFindDataResult<CFunction>> oMemberFunctionVector = m_oCodePareser.FindMemberFunctions( oFileContentString );
    FilterResults( oMemberFunctionVector, oDeveloperString );

    std::vector<SFindDataResult<CFunction>> oGlobalFunctionVector = m_oCodePareser.FindGlobalFunctions( oFileContentString );
    FilterResults( oGlobalFunctionVector, oDeveloperString );

    oSourceFile.SetMemberFunctions( std::move( oMemberFunctionVector ) );
    oSourceFile.SetGlobalFunctions( std::move( oGlobalFunctionVector ) );

    for ( std::unique_ptr<CCodeAnalyzerModule>& upoAnalyzerModule : m_oAnalyzerModuleVector )
    {
        upoAnalyzerModule->ProcessSourceFile( oSourceFile );
    }
}

// ^^x
// void CCodeAnalyzer::FilterResults
// 3BGO JIRA-238 24-09-2020
void CCodeAnalyzer::FilterResults( std::vector<SFindDataResult<CFunction>>& oFunctionVector, std::optional<std::string> oDeveloperString ) const
{
    if ( oDeveloperString.has_value() )
    {
        const std::vector<SFindDataResult<CFunction>>::iterator oFunctionVectorIt = std::remove_if( oFunctionVector.begin(), oFunctionVector.end(), [oDeveloperString]( const SFindDataResult<CFunction>& oFunction )
        {
            if ( oFunction.oData.GetInformation().has_value() )
            {
                return oFunction.oData.GetInformation()->oAuthorString != *oDeveloperString;
            }

            return true;
        } );

        oFunctionVector.erase( oFunctionVectorIt, oFunctionVector.cend() );
    }
}

// ^^x
// void CCodeAnalyzer::PrintProgress
// 3BGO JIRA-238 24-09-2020
void CCodeAnalyzer::PrintProgress( const unsigned int uiFileNumber, const std::size_t uiFileCount ) const
{
    const std::size_t uiCurrentProgressPos = uiFileNumber * 100u / uiFileCount;
    const std::string oCompleteProgressString( uiCurrentProgressPos / 2u, static_cast<char>( 219 ) );

    std::string oProgressBarString( 50u, static_cast<char>( 176 ) );
    oProgressBarString.replace( 0u, uiCurrentProgressPos / 2u, oCompleteProgressString );

    const std::string oProcessCodeFileNumberString = std::to_string( uiFileNumber );
    const std::string oProcessCodeFileCountString = std::to_string( uiFileCount );
    const std::string oCurrentProgressPosString = std::to_string( uiCurrentProgressPos );

    CConsoleInterface::Print( "  Processing " + oProcessCodeFileNumberString + "/" + oProcessCodeFileCountString + " file " + oProgressBarString + " " + oCurrentProgressPosString + "%\r" );
}
