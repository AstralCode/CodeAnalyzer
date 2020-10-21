#pragma once

enum class EProgramStatusCodes
{
	eSuccess,
	eIncorrectArgumentCount,
	eIncorrectInputDirectoryArgument,
	eIncorrectOptionArgument,
	eOpenInputFileError,
	eOpenOutputFileError,
	eProcessHeaderCodeFileError,
	eProcessSourceCodeFileError,
	eCreateOutputDirectoryError
};
