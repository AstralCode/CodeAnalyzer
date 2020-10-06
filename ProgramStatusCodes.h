#pragma once

enum class EProgramStatusCodes
{
	eSuccess,
	eIncorrectArgumentCount,
	eInputDirectoryNotExists,
	eOutputDirectoryNotExists,
	eOpenInputFileError,
	eOpenOutputFileError,
	eProcessHeaderCodeFileError,
	eProcessSourceCodeFileError,
};
