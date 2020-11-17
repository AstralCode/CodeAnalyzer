#include "CodeAnalyzer.h"

#include <fstream>
#include <algorithm>

#include "ConsoleInterface.h"
#include "SourceFile.h"
#include "HeaderFile.h"
#include "Utility.h"

// ^^x
// const CStatisticsCollection& CCodeAnalyzer::GetStatisticsCollection
// 3BGO JIRA-238 24-09-2020
const CStatisticsCollection& CCodeAnalyzer::GetStatisticsCollection() const
{
    return m_oStatisticsCollection;
}

// ^^x
// EProgramStatusCodes CCodeAnalyzer::Execute
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CCodeAnalyzer::Execute( const std::filesystem::path& oInputDirectoryPath, std::optional<std::string> oDeveloperString )
{
    EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };
    std::size_t uiProcessCodeFileNumber{ 0u };
    std::size_t uiCodeFileCount{ 0u };

    OnPreExecute( oInputDirectoryPath, uiCodeFileCount );

    m_oStatisticsCollection[EStatisticsTypes::eFileCount] = { "Files", uiCodeFileCount };

    std::filesystem::recursive_directory_iterator oDirectoryIterator{ oInputDirectoryPath };
    for ( const std::filesystem::path& oFilePath : oDirectoryIterator )
    {
        const ECodeFileTypes eFileType = CheckFileType( oFilePath );
        if ( eFileType != ECodeFileTypes::eUnknown )
        {
            ProcessCodeFile( eFileType, oFilePath, oDeveloperString );
            PrintProgress( ++uiProcessCodeFileNumber, uiCodeFileCount );
        }
    }

    OnPostExecute( eStatus );

    return eStatus;
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
        oFileContentString.assign( std::istreambuf_iterator<char>{ oFileStream }, {} );
    }
    else
    {
        eStatus = EProgramStatusCodes::eOpenInputFileError;
    }

    return eStatus;
}

// ^^x
// EProgramStatusCodes CCodeAnalyzer::ProcessCodeFile
// 3BGO JIRA-238 24-09-2020
EProgramStatusCodes CCodeAnalyzer::ProcessCodeFile( const ECodeFileTypes eFileType, const std::filesystem::path& oFilePath, std::optional<std::string> oDeveloperString )
{
    std::string oCodeString{};

    EProgramStatusCodes eStatus = ReadFileContent( oFilePath, oCodeString );
    if ( eStatus == EProgramStatusCodes::eSuccess )
    {
        PreProcessFileContent( oCodeString );

        switch ( eFileType )
        {
            case ECodeFileTypes::eHeader:
                {
                    ProcessHeaderFile( oFilePath, oCodeString, oDeveloperString );
                    break;
                }
            case ECodeFileTypes::eSource:
                {
                    ProcessSourceFile( oFilePath, oCodeString, oDeveloperString );
                    break;
                }
            case ECodeFileTypes::eUnknown:
            default:
                eStatus = EProgramStatusCodes::eUnknownInputFileType;
                break;
        }
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
    m_oCodePareser.RemoveDeclarations( oFileContentString );
    m_oCodePareser.RemoveCallingConvetions( oFileContentString );
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
        upoAnalyzerModule->ProcessHeaderFile( oHeaderFile, m_oStatisticsCollection );
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
        upoAnalyzerModule->ProcessSourceFile( oSourceFile, m_oStatisticsCollection );
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
// void CCodeAnalyzer::OnPreExecute
// 3BGO JIRA-238 22-10-2020
void CCodeAnalyzer::OnPreExecute( const std::filesystem::path& oInputDirectoryPath, std::size_t& uiCodeFileCount )
{
    CConsoleInterface::PrintLine( "Code directory: \"" + oInputDirectoryPath.string() + "\"", true );
    CConsoleInterface::Print( "Calculating the number of C++ code files. Please wait...\r" );

    const std::size_t uiHeaderFileCount = CountNumberCodeFiles( oInputDirectoryPath, ECodeFileTypes::eHeader );
    const std::size_t uiSourceFileCount = CountNumberCodeFiles( oInputDirectoryPath, ECodeFileTypes::eSource );
    uiCodeFileCount = uiHeaderFileCount + uiSourceFileCount;

    CConsoleInterface::ClearLine();
    CConsoleInterface::PrintLine( "C++ Header files: " + std::to_string( uiHeaderFileCount ), true );
    SleepThread( 1ull );
    CConsoleInterface::PrintLine( "C++ Source files: " + std::to_string( uiSourceFileCount ), true );
    SleepThread( 1ull );
    CConsoleInterface::Print( "Code analysis in progress...\r" );

    for ( std::unique_ptr<CCodeAnalyzerModule>& upoAnalyzerModule : m_oAnalyzerModuleVector )
    {
        upoAnalyzerModule->OnPreExecute( m_oStatisticsCollection );
    }
}

// ^^x
// void CCodeAnalyzer::OnPostExecute
// 3BGO JIRA-238 22-10-2020
void CCodeAnalyzer::OnPostExecute( const EProgramStatusCodes eStatus )
{
    if ( eStatus == EProgramStatusCodes::eSuccess )
    {
        for ( std::unique_ptr<CCodeAnalyzerModule>& upoAnalyzerModule : m_oAnalyzerModuleVector )
        {
            upoAnalyzerModule->OnPostExecute( m_oStatisticsCollection );
        }

        CConsoleInterface::ClearLine();
        CConsoleInterface::PrintLine( "Analysis complete!", true );
    }
}

// ^^x
// std::size_t CCodeAnalyzer::CountNumberCodeFiles
// 3BGO JIRA-238 24-09-2020
std::size_t CCodeAnalyzer::CountNumberCodeFiles( const std::filesystem::path& oDirectoryPath ) const
{
    return std::count_if( std::filesystem::recursive_directory_iterator{ oDirectoryPath },
                          std::filesystem::recursive_directory_iterator{},
                          [this]( const std::filesystem::path& oFilePath ) { return IsCodeFile( oFilePath ); } );
}

// ^^x
// std::size_t CCodeAnalyzer::CountNumberCodeFiles
// 3BGO JIRA-238 25-10-2020
std::size_t CCodeAnalyzer::CountNumberCodeFiles( const std::filesystem::path& oDirectoryPath, const ECodeFileTypes eCodeFileType ) const
{
    return std::count_if( std::filesystem::recursive_directory_iterator{ oDirectoryPath },
                          std::filesystem::recursive_directory_iterator{},
                          [this, eCodeFileType]( const std::filesystem::path& oFilePath )
                          {
                              const ECodeFileTypes eFileType = CheckFileType( oFilePath );
                              return eFileType == eCodeFileType;
                          } );
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
// ECodeFileTypes CCodeAnalyzer::CheckFileType
// 3BGO JIRA-238 24-09-2020
ECodeFileTypes CCodeAnalyzer::CheckFileType( const std::filesystem::path& oFilePath ) const
{
    ECodeFileTypes eType{ ECodeFileTypes::eUnknown };

    if ( std::filesystem::is_regular_file( oFilePath ) )
    {
        if ( oFilePath.has_extension() )
        {
            if ( oFilePath.extension() == ".h" )
            {
                eType = ECodeFileTypes::eHeader;
            }
            else if ( oFilePath.extension() == ".cpp" )
            {
                eType = ECodeFileTypes::eSource;
            }
        }
    }

    return eType;
}

// ^^x
// bool CCodeAnalyzer::IsCodeFile
// 3BGO JIRA-238 06-10-2020
bool CCodeAnalyzer::IsCodeFile( const std::filesystem::path& oFilePath ) const
{
    return CheckFileType( oFilePath ) != ECodeFileTypes::eUnknown;
}

// ^^x
// void CCodeAnalyzer::PrintProgress
// 3BGO JIRA-238 24-09-2020
void CCodeAnalyzer::PrintProgress( const std::size_t uiFileNumber, const std::size_t uiFileCount ) const
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
