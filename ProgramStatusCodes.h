#pragma once

enum class EProgramStatusCodes
{
	eSuccess,
	eIncorrectArgumentCount,
	eIncorrectInputDirectoryArgument,
	eIncorrectOutputDirectoryArgument,
	eIncorrectDataSeparatorArgument,
	eIncorrectOptionArgument,
	eOpenInputFileError,
	eOpenOutputFileError,
	eProcessHeaderCodeFileError,
	eProcessSourceCodeFileError,
};
