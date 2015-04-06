#pragma once;

#include "CallbackInfo.h"

typedef void(*LoggingFunction)(int level, const char *message);

typedef int(*IntCallback)(const Flathead::CallbackInfo& args);
typedef bool(*BoolCallback)(const Flathead::CallbackInfo& args);
typedef double(*NumberCallback)(const Flathead::CallbackInfo& args);
typedef char * (*StringCallback)(const Flathead::CallbackInfo& args);
typedef void(*VoidCallback)(const Flathead::CallbackInfo& args);

enum MessageTypes
{
	Log = 0,
	Info,
	Debug,
	Warning,
	Error
};

enum ResultTypes
{
	RESString = 0,
	RESNumber,
	RESBool,
	RESInteger,
	RESFunction,
	RESObject,
	RESUndefined,
	RESFailure
};