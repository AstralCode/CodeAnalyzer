#include "ConsoleInterface.h"
#include "CommandLineHandler.h"
#include "CodeAnalyzer.h"
#include "CsvStatisticsReportWriter.h"
#include "CodeLineCountModule.h"
#include "FunctionCountModule.h"
#include "FunctionLengthModule.h"
#include "FunctionArgsCountModule.h"
#include "VariableGlobalCountModule.h"
#include "VariableRulesModule.h"
#include "DialogUsesDatabaseModule.h"
#include "Utility.h"
#include "DateTimeHelper.h"
#include "StringHelper.h"

// ^^x
// EProgramStatusCodes PrepareDirectory
// 3BGO JIRA-238 23-10-2020
EProgramStatusCodes PrepareDirectory( const std::string& oDirectoryNameString, std::filesystem::path& oOutputDirectoryPath )
{
	EProgramStatusCodes eStatus{ EProgramStatusCodes::eSuccess };

	oOutputDirectoryPath = std::filesystem::current_path().append( oDirectoryNameString );

	if ( !std::filesystem::exists( oOutputDirectoryPath ) )
	{
		std::filesystem::create_directories( oOutputDirectoryPath );
	}

	if ( !std::filesystem::exists( oOutputDirectoryPath ) )
	{
		eStatus = EProgramStatusCodes::eCreateDirectoryError;
	}

	return eStatus;
}

// ^^x
// std::filesystem::path PrepareReportPath
// 3BGO JIRA-238 24-09-2020
std::filesystem::path PrepareReportPath( const std::filesystem::path& oOutputDirectoryPath, std::optional<std::string> oReportPrefixNameString )
{
	const std::string oCurrentDateString = CDateTimeHelper::CurrentDate();
	const std::string oCurrentTimeString = CStringHelper::Replace( CDateTimeHelper::CurrentTime(), ':', '-' );

	std::string oFilenameString{ "Report--" + oCurrentDateString + "--" + oCurrentTimeString + ".csv" };

	if ( oReportPrefixNameString.has_value() )
	{
		oFilenameString = *oReportPrefixNameString + "--" + oFilenameString;
	}

	return oOutputDirectoryPath / oFilenameString;
};

// ^^x
// int main
// 3BGO JIRA-238 24-09-2020
int main( int iArgumentCount, char* apcArguments[] )
{
	CConsoleInterface::PrintLine( "Code Analyzer [Version 1.2] (c) 2020 IN-Software" );
	CConsoleInterface::NewLine();

	CCommandLineHandler oCommandLineHandler{ iArgumentCount, apcArguments };

	CCodeAnalyzer oCodeAnalyzer{};
	CCsvStatisticsReportWriter oStatisticsReportWriter{};
	SCommandLineArgumentDataset oCommandLineArgumentDataset{};

	EProgramStatusCodes eStatus = oCommandLineHandler.HandleArguments( oCommandLineArgumentDataset );
	if ( eStatus == EProgramStatusCodes::eSuccess )
	{
		std::filesystem::path oOutputDirectoryPath{};

		eStatus = PrepareDirectory( "Reports", oOutputDirectoryPath );
		if ( eStatus == EProgramStatusCodes::eSuccess )
		{
			const std::filesystem::path oReportPath = PrepareReportPath( oOutputDirectoryPath, oCommandLineArgumentDataset.oReportPrefixNameString );
			const bool bExtendedReportMode = oCommandLineArgumentDataset.oReportModeString.has_value();

			std::filesystem::path oLoggerDirectoryPath = oReportPath;
			oLoggerDirectoryPath.replace_extension();

			if ( bExtendedReportMode )
			{
				std::filesystem::create_directories( oLoggerDirectoryPath );
			}

			oCodeAnalyzer.AddAnalyzerModule<CCodeLineCountModule>( oLoggerDirectoryPath, bExtendedReportMode );
			oCodeAnalyzer.AddAnalyzerModule<CFunctionCountModule>( oLoggerDirectoryPath, bExtendedReportMode );
			oCodeAnalyzer.AddAnalyzerModule<CFunctionLengthModule>( oLoggerDirectoryPath, bExtendedReportMode );
			oCodeAnalyzer.AddAnalyzerModule<CFunctionArgsCountModule>( oLoggerDirectoryPath, bExtendedReportMode );
			oCodeAnalyzer.AddAnalyzerModule<CVariableGlobalCountModule>( oLoggerDirectoryPath, bExtendedReportMode );
			oCodeAnalyzer.AddAnalyzerModule<CVariableRulesModule>( oLoggerDirectoryPath, bExtendedReportMode );
			oCodeAnalyzer.AddAnalyzerModule<CDialogUsesDatabaseModule>( oLoggerDirectoryPath, bExtendedReportMode );

			eStatus = oCodeAnalyzer.Execute( oCommandLineArgumentDataset.oInputDirectoryPath, oCommandLineArgumentDataset.oDeveloperString );
			if ( eStatus == EProgramStatusCodes::eSuccess )
			{
				eStatus = oStatisticsReportWriter.CreateReport( oCodeAnalyzer.GetStatisticsCollection(), oReportPath, oCommandLineArgumentDataset.oReportPrefixNameString );
				if ( eStatus == EProgramStatusCodes::eSuccess )
				{
					CConsoleInterface::PrintLine( "Report created at: \"" + oReportPath.string() + "\"" );
				}
			}
		}
	}
	else
	{
		CConsoleInterface::PrintLine( oCommandLineHandler.GetUsageMessage() );
	}

	return static_cast<int>( eStatus );
}
