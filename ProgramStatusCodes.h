#pragma once

enum class EProgramStatusCodes
{
	eSuccess,
	eIncorrectArgumentCount,
	eIncorrectInputDirectoryArgument,
	eIncorrectOutputDirectoryArgument,
	eIncorrectOptionArgument,
	eOpenInputFileError,
	eOpenOutputFileError,
	eProcessHeaderCodeFileError,
	eProcessSourceCodeFileError,
};
