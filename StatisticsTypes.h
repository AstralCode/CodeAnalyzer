#pragma once

enum class EStatisticsTypes
{
	eFileCount,
	eCodeLineCount,
	eFunctionCount,
	eGlobalFunctionCount,
	eGlobalFunctionPercent,
	eFunctionLengthQPCount,
	eFunctionLengthQPPercent,
	eFunctionLengthHPCount,
	eFunctionLengthHPPercent,
	eFunctionLength1PCount,
	eFunctionLength1PPercent,
	eFunctionLength2PCount,
	eFunctionLength2PPercent,
	eFunctionLength4PCount,
	eFunctionLength4PPercent,
	eFunctionLength4PPlusCount,
	eFunctionLength4PPlusPercent,
	eFunction6PlusArgsCount,
	eFunction6PlusArgsPercent,
	eGlobalVariableCount,
	eVariableIncorrectNameCount,
	eDialogClassesCount,
	eDialogUsesDatabaseCount,
	eDialogUsesDatabasePercent
};
