#pragma once

enum class EProgramStatusCodes
{
	eSuccess,
	eIncorrectArgumentCount,
	eIncorrectInputDirectoryArgument,
	eIncorrectOptionArgument,
	eOpenInputFileError,
	eOpenOutputFileError,
	eUnknownInputFileType,
	eProcessHeaderCodeFileError,
	eProcessSourceCodeFileError,
	eCreateOutputDirectoryError
};
