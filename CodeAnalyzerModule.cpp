#include "CodeAnalyzerModule.h"

#include <fstream>

// ^^x
// CCodeAnalyzerModule::CCodeAnalyzerModule
// 3BGO NTP-1 09-11-2020
CCodeAnalyzerModule::CCodeAnalyzerModule( const std::filesystem::path& oLoggerDirectoryPath, const bool bLoggingEnabled ) :
	m_oLogger{ oLoggerDirectoryPath },
	m_bLoggingEnabled{ bLoggingEnabled }
{

}

// ^^x
// bool CCodeAnalyzerModule::IsLoggingEnabled
// 3BGO NTP-1 09-11-2020
bool CCodeAnalyzerModule::IsLoggingEnabled() const
{
	return m_bLoggingEnabled;
}
