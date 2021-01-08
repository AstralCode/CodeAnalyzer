#include "CodeAnalyzerLogger.h"

#include "StringHelper.h"

// ^^x
// CCodeAnalyzerLogger::CCodeAnalyzerLogger
// 3BGO JIRA-238 10-11-2020
CCodeAnalyzerLogger::CCodeAnalyzerLogger( const std::filesystem::path& oDirectoryPath ) :
	m_oDirectoryPath{ oDirectoryPath }
{

}

// ^^x
// void CCodeAnalyzerLogger::Open
// 3BGO JIRA-238 10-11-2020
void CCodeAnalyzerLogger::Open( const std::string& oFilenameString )
{
	if ( !m_oFileStream.is_open() )
	{
		if ( std::filesystem::exists( m_oDirectoryPath ) )
		{
			m_oFilenamePath = m_oDirectoryPath / oFilenameString;
			m_oFileStream.open( m_oFilenamePath.string(), std::fstream::out );
		}
	}
}

// ^^x
// void CCodeAnalyzerLogger::Remove
// 3BGO JIRA-238 10-11-2020
void CCodeAnalyzerLogger::Remove()
{
	if ( m_oFileStream.is_open() )
	{
		m_oFileStream.close();
		std::filesystem::remove( m_oFilenamePath );
	}
}

// ^^x
// void CCodeAnalyzerLogger::Write
// 3BGO JIRA-238 10-11-2020
void CCodeAnalyzerLogger::Write( const std::string& oMessageString )
{
	if ( m_oFileStream.is_open() )
	{
		m_oFileStream << oMessageString;
	}
}

// ^^x
// void CCodeAnalyzerLogger::WriteLine
// 3BGO JIRA-238 10-11-2020
void CCodeAnalyzerLogger::WriteLine( const std::string& oMessageString )
{
	if ( m_oFileStream.is_open() )
	{
		m_oFileStream << oMessageString << '\n';
	}
}

// ^^x
// void CCodeAnalyzerLogger::Log
// 3BGO JIRA-238 10-11-2020
void CCodeAnalyzerLogger::Log( const SFindDataResult<CVariable>& oVariable, bool bIsMember )
{
	if ( bIsMember )
	{
		Write( "(member) " );
	}

	WriteLine( CStringHelper::Trim( CStringHelper::SimplifyString( oVariable.oRegexMatchString ) ) );
}

// ^^x
// void CCodeAnalyzerLogger::Log
// 3BGO JIRA-238 10-11-2020
void CCodeAnalyzerLogger::Log( const SFindDataResult<CFunction>& oFunction )
{
	WriteLine( CStringHelper::Trim( CStringHelper::SimplifyString( oFunction.oRegexMatchString ) ) );
}
