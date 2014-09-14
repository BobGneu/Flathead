// Copyright 2013 Gneu, LLC. All Rights Reserved.

#include "FlatheadPCH.h"
#include "Flathead.h"

#include <fstream>

#include "libplatform/libplatform.h"
#include "StringConv.h"

DEFINE_LOG_CATEGORY(FH);

#define BINDING_VERSION "1.1.0"

using namespace v8;

Flathead_impl* Flathead_impl::accessor = NULL;

#define FUNCTION_PROTOTYPE(target, name, fn) \
	target->PrototypeTemplate()->Set(String::NewFromUtf8(GetIsolate(), name, String::kInternalizedString), FunctionTemplate::New(GetIsolate(), fn));

#define ACCESSOR_PROTOTYPE(target, name, fn) \
	target->PrototypeTemplate()->SetAccessor(String::NewFromUtf8(GetIsolate(), name, String::kInternalizedString), fn);

#define NUMBER_PROTOTYPE(target, name, val) \
	target->PrototypeTemplate()->Set(String::NewFromUtf8(GetIsolate(), name, String::kInternalizedString), Number::New(GetIsolate(), val))

#define STRING_PROTOTYPE(target, name, val) \
	target->PrototypeTemplate()->Set(String::NewFromUtf8(GetIsolate(), name, String::kInternalizedString), String::NewFromUtf8(GetIsolate(), val))


void Flathead_impl::StartupModule()
{
	V8::InitializeICU();

	v8::Platform* platform = v8::platform::CreateDefaultPlatform();
	v8::V8::InitializePlatform(platform);

	accessor = this;

	SetIsolate(v8::Isolate::New());
	Isolate::Scope isolate_scope(GetIsolate());
	HandleScope handle_scope(GetIsolate());

	Handle<Context> context = CreateGlobalContext();
	globalContext.Reset(GetIsolate(), context);

	GetIsolate()->SetEventLogger(Flathead_impl::LoggerCallback);

	LoadScript("Initialization.js");
}

void Flathead_impl::LoggerCallback(const char* message, int status)
{
	UE_LOG(FH, Log, TEXT("%d - %s"), status, UTF8_TO_TCHAR(message));
}

Handle<Context> Flathead_impl::CreateGlobalContext()
{
	Local<ObjectTemplate> objTemplate = ObjectTemplate::New(GetIsolate());

	DefineLoggingFunctions(objTemplate);
	DefineUE4Functions(objTemplate);
	DefineV8Functions(objTemplate);
	DefineRequire(objTemplate);
	DefineMath(objTemplate);

	return Context::New(GetIsolate(), NULL, objTemplate);
}

void Flathead_impl::ShutdownModule()
{
	V8::Dispose();
}

FString Flathead_impl::GetCoreScriptsDirectory()
{
	return FPaths::GamePluginsDir() + "Flathead/Scripts/";
}

FString Flathead_impl::GetGameScriptsDirectory()
{
	return FPaths::GameDir() + "Scripts/";
}

bool Flathead_impl::LoadScript(char* fileName)
{
	UE_LOG(FH, Log, TEXT("Attempting to load script %s"), *FString(fileName));
	if (LoadGameScript(fileName) || LoadCoreScript(fileName))
	{
		return true;
	}

	return false;
}

bool Flathead_impl::LoadGameScript(char* fileName)
{
	bool result = false;

	UE_LOG(FH, Log, TEXT("Game: %s"), *(GetGameScriptsDirectory() + fileName));
	std::ifstream file(*(GetGameScriptsDirectory() + fileName), std::ios::binary);

	if (!file)
		return false;

	if (file.is_open())
	{
		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(0, file.beg);

		char * data = new char[length + 1];
		data[length] = 0;

		if (!file.read(data, length))
		{
			UE_LOG(FH, Error, TEXT("Could not load file - Incorrect format. %d %s"), file.gcount(), *fileName);
		}
		else
		{
			result = Execute(data, fileName);
		}
	}

	file.close();

	return false;
}

bool Flathead_impl::LoadGameScript(FString filename)
{
	return LoadGameScript(TCHAR_TO_ANSI(*filename));
}

bool Flathead_impl::LoadCoreScript(char* filename)
{
	bool result = false;

	UE_LOG(FH, Log, TEXT("Core: %s"), *(GetCoreScriptsDirectory() + filename));
	std::ifstream file(*(GetCoreScriptsDirectory() + filename), std::ios::binary);

	if (!file)
		return false;

	if (file.is_open())
	{
		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(0, file.beg);

		char * data = new char[length + 1];
		data[length] = 0;

		if (!file.read(data, length))
		{
			UE_LOG(FH, Error, TEXT("Could not load file - Incorrect format. %d %s"), file.gcount(), *filename);
		}
		else
		{
			result = Execute(data, filename);
		}
	}

	file.close();

	return result;
}

bool Flathead_impl::Execute(FString data, FString filename)
{
	return Execute(TCHAR_TO_ANSI(*data), TCHAR_TO_ANSI(*filename));
}

bool Flathead_impl::Execute(char * data, char * filename)
{
	FString result;
	TryCatch try_catch;

	HandleScope handle_scope(GetIsolate());

	Local<Context> context = Local<Context>::New(GetIsolate(), globalContext);
	Context::Scope context_scope(context);

	Handle<String> source = String::NewFromUtf8(GetIsolate(), data);
	Handle<String> name = String::NewFromUtf8(GetIsolate(), filename);

	ScriptOrigin origin(name);
	Handle<Script> script = Script::Compile(source, &origin);

	Local<Value> jsResult = script->Run();

	if (jsResult.IsEmpty())
	{
		String::Utf8Value stacktrace(try_catch.StackTrace());
		UE_LOG(FH, Error, TEXT("%s"), UTF8_TO_TCHAR(*stacktrace));
		return false;
	}
	
	String::Utf8Value outResult(jsResult);
	UE_LOG(FH, Log, TEXT("Result: %s"), UTF8_TO_TCHAR(*outResult));
	return true;
}

FString Flathead_impl::ArgsToFstr(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	bool first = true;
	FString fstr;

	for (int i = 0; i < args.Length(); i++)
	{
		HandleScope handle_scope(args.GetIsolate());
		String::Utf8Value str(args[i]);

		if (first)
			first = false;
		else
			fstr += " ";

		fstr += *str;
	}

	return fstr;
}

#pragma region V8 Methods

void Flathead_impl::DefineV8Functions(Local<ObjectTemplate> globalTemplate)
{
	HandleScope scope(GetIsolate());

	Handle<Context> context = Context::New(GetIsolate());
	Context::Scope ContextScope(context);

	Local<FunctionTemplate> v8_tmp = v8::FunctionTemplate::New(GetIsolate());

	ACCESSOR_PROTOTYPE(v8_tmp, "version", Flathead_impl::GetV8Version);
	ACCESSOR_PROTOTYPE(v8_tmp, "bindingVersion", Flathead_impl::GetBindingVersion);

	globalTemplate->Set(String::NewFromUtf8(GetIsolate(), "v8"), v8_tmp->GetFunction()->NewInstance(), ReadOnly);
}

void Flathead_impl::GetV8Version(Local<String> name, const PropertyCallbackInfo<Value>& info)
{
	info.GetReturnValue().Set(String::NewFromUtf8(info.GetIsolate(), V8::GetVersion(), String::kNormalString));
}

void Flathead_impl::GetBindingVersion(Local<String> name, const PropertyCallbackInfo<Value>& info)
{
	info.GetReturnValue().Set(String::NewFromUtf8(info.GetIsolate(), BINDING_VERSION, String::kNormalString));
}

#pragma endregion

#pragma region Logging Methods

void Flathead_impl::DefineLoggingFunctions(Local<ObjectTemplate> globalTemplate)
{
	HandleScope scope(GetIsolate());

	Handle<Context> context = Context::New(GetIsolate());
	Context::Scope ContextScope(context);

	Local<FunctionTemplate> log_tmp = FunctionTemplate::New(GetIsolate());

	FUNCTION_PROTOTYPE(log_tmp, "log", Flathead_impl::LogCallback);
	FUNCTION_PROTOTYPE(log_tmp, "display", Flathead_impl::DisplayCallback);
	FUNCTION_PROTOTYPE(log_tmp, "warning", Flathead_impl::WarningCallback);
	FUNCTION_PROTOTYPE(log_tmp, "error", Flathead_impl::ErrorCallback);
	FUNCTION_PROTOTYPE(log_tmp, "fatal", Flathead_impl::FatalCallback);

	globalTemplate->Set(String::NewFromUtf8(GetIsolate(), "game"), log_tmp->GetFunction()->NewInstance(), ReadOnly);
}

void Flathead_impl::LogCallback(const FunctionCallbackInfo<Value>& info)
{
	UE_LOG(FH, Log, TEXT("%s"), *ArgsToFstr(info));

	info.GetReturnValue().Set(true);
}

void Flathead_impl::DisplayCallback(const FunctionCallbackInfo<Value>& info)
{
	UE_LOG(FH, Display, TEXT("%s"), *ArgsToFstr(info));

	info.GetReturnValue().Set(true);
}

void Flathead_impl::WarningCallback(const FunctionCallbackInfo<Value>& info)
{
	UE_LOG(FH, Warning, TEXT("%s"), *ArgsToFstr(info));

	info.GetReturnValue().Set(true);
}

void Flathead_impl::ErrorCallback(const FunctionCallbackInfo<Value>& info)
{
	UE_LOG(FH, Error, TEXT("%s"), *ArgsToFstr(info));

	info.GetReturnValue().Set(true);
}

void Flathead_impl::FatalCallback(const FunctionCallbackInfo<Value>& info)
{
	UE_LOG(FH, Fatal, TEXT("%s"), *ArgsToFstr(info));

	info.GetReturnValue().Set(true);
}

#pragma endregion 

#pragma region UE4 Functions

void Flathead_impl::DefineUE4Functions(Local<ObjectTemplate> globalTemplate)
{
	HandleScope scope(GetIsolate());

	Handle<Context> context = Context::New(GetIsolate());
	Context::Scope ContextScope(context);

	Local<FunctionTemplate> game_tmp = FunctionTemplate::New(GetIsolate());

	ACCESSOR_PROTOTYPE(game_tmp, "version", Flathead_impl::GetVersion);

	globalTemplate->Set(String::NewFromUtf8(GetIsolate(), "game"), game_tmp->GetFunction()->NewInstance(), ReadOnly);
}

void Flathead_impl::GetVersion(Local<String> name, const PropertyCallbackInfo<Value>& info)
{
	info.GetReturnValue().Set(String::NewFromUtf8(info.GetIsolate(), TCHAR_TO_UTF8(*GEngineVersion.ToString())));
}

#pragma endregion 

#pragma region Require 

void Flathead_impl::DefineRequire(Local<ObjectTemplate> objTemplate)
{
	HandleScope scope(GetIsolate());

	Handle<Context> context = Context::New(GetIsolate());
	Context::Scope ContextScope(context);

	Local<FunctionTemplate> require = FunctionTemplate::New(GetIsolate(), Flathead_impl::Require);

	objTemplate->Set(String::NewFromUtf8(GetIsolate(), "require"), require->GetFunction(), ReadOnly);
}

void Flathead_impl::Require(const FunctionCallbackInfo<Value>& info)
{
	FString target = ArgsToFstr(info) + ".js";

	UE_LOG(FH, Log, TEXT("%s"), *target);

	if (accessor != NULL)
	{
		info.GetReturnValue().Set(accessor->LoadScript(TCHAR_TO_ANSI(*target)));
	}
	else
	{
		UE_LOG(FH, Error, TEXT("Failed to load script due to accessor being missing: %s"), *target);
	}
}

#pragma endregion

#pragma region UObject

void Flathead_impl::DefineUObject(v8::Local<v8::ObjectTemplate> globalTemplate)
{
	HandleScope scope(GetIsolate());

	Handle<Context> context = Context::New(GetIsolate());
	Context::Scope ContextScope(context);

	Local<FunctionTemplate> uobject = FunctionTemplate::New(GetIsolate());

	globalTemplate->Set(String::NewFromUtf8(GetIsolate(), "UObject"), uobject->GetFunction(), ReadOnly);
}

#pragma endregion

#pragma region AActor

void Flathead_impl::DefineActor(v8::Local<v8::ObjectTemplate> globalTemplate)
{
	HandleScope scope(GetIsolate());

	Handle<Context> context = Context::New(GetIsolate());
	Context::Scope ContextScope(context);

	Local<FunctionTemplate> actor = FunctionTemplate::New(GetIsolate());

	globalTemplate->Set(String::NewFromUtf8(GetIsolate(), "Actor"), actor->GetFunction(), ReadOnly);
}

#pragma endregion

#pragma region Math

/*

	TODO:
	class  FVector;
	class  FVector4;
	class  FPlane;
	class  FBox;
	class  FRotator;
	class  FMatrix;
	class  FQuat;
	class  FTwoVectors;
	class  FTransform;
	class  FSphere;
	struct FVector2D;
	struct FLinearColor;

	Local<ObjectTemplate> fvector = ObjectTemplate::New(GetIsolate());

	globalTemplate->Set(String::NewFromUtf8(GetIsolate(), "FVector"), fvector->NewInstance(), ReadOnly);
	
*/
void Flathead_impl::DefineMath(v8::Local<v8::ObjectTemplate> globalTemplate)
{
	HandleScope scope(GetIsolate());

	Handle<Context> context = Context::New(GetIsolate());
	Context::Scope ContextScope(context);

	Local<FunctionTemplate> umath = FunctionTemplate::New(GetIsolate());
	
	// Constants
	NUMBER_PROTOTYPE(umath, "PI", PI);
	NUMBER_PROTOTYPE(umath, "SMALL_NUMBER", SMALL_NUMBER);
	NUMBER_PROTOTYPE(umath, "KINDA_SMALL_NUMBER", KINDA_SMALL_NUMBER);
	NUMBER_PROTOTYPE(umath, "BIG_NUMBER", BIG_NUMBER);
	NUMBER_PROTOTYPE(umath, "EULERS_NUMBER", EULERS_NUMBER);
	NUMBER_PROTOTYPE(umath, "MAX_FLT", MAX_FLT);
	NUMBER_PROTOTYPE(umath, "INV_PI", INV_PI);
	NUMBER_PROTOTYPE(umath, "HALF_PI", HALF_PI);
	NUMBER_PROTOTYPE(umath, "DELTA", DELTA);

	// Misc. constants 
	NUMBER_PROTOTYPE(umath, "FLOAT_NORMAL_THRESH", FLOAT_NORMAL_THRESH);
	NUMBER_PROTOTYPE(umath, "THRESH_POINT_ON_PLANE", THRESH_POINT_ON_PLANE);
	NUMBER_PROTOTYPE(umath, "THRESH_POINT_ON_SIDE", THRESH_POINT_ON_SIDE);
	NUMBER_PROTOTYPE(umath, "THRESH_POINTS_ARE_SAME", THRESH_POINTS_ARE_SAME);
	NUMBER_PROTOTYPE(umath, "THRESH_POINTS_ARE_NEAR", THRESH_POINTS_ARE_NEAR);
	NUMBER_PROTOTYPE(umath, "THRESH_NORMALS_ARE_SAME", THRESH_NORMALS_ARE_SAME);
	NUMBER_PROTOTYPE(umath, "THRESH_VECTORS_ARE_NEAR", THRESH_VECTORS_ARE_NEAR);
	NUMBER_PROTOTYPE(umath, "THRESH_SPLIT_POLY_WITH_PLANE", THRESH_SPLIT_POLY_WITH_PLANE);
	NUMBER_PROTOTYPE(umath, "THRESH_SPLIT_POLY_PRECISELY", THRESH_SPLIT_POLY_PRECISELY);
	NUMBER_PROTOTYPE(umath, "THRESH_ZERO_NORM_SQUARED", THRESH_ZERO_NORM_SQUARED);
	NUMBER_PROTOTYPE(umath, "THRESH_VECTORS_ARE_PARALLEL", THRESH_VECTORS_ARE_PARALLEL);
	
	// Functions
	FUNCTION_PROTOTYPE(umath, "abs", Flathead_impl::Math_Abs);
	FUNCTION_PROTOTYPE(umath, "acos", Flathead_impl::Math_ACos);
	FUNCTION_PROTOTYPE(umath, "asin", Flathead_impl::Math_ASin);
	FUNCTION_PROTOTYPE(umath, "atan", Flathead_impl::Math_ATan);
	FUNCTION_PROTOTYPE(umath, "atan2", Flathead_impl::Math_ATan2);
	FUNCTION_PROTOTYPE(umath, "ceil", Flathead_impl::Math_Ceil);
	FUNCTION_PROTOTYPE(umath, "clamp", Flathead_impl::Math_Clamp);
	FUNCTION_PROTOTYPE(umath, "clampAngle", Flathead_impl::Math_ClampAngle);
	FUNCTION_PROTOTYPE(umath, "cos", Flathead_impl::Math_Cos);
	FUNCTION_PROTOTYPE(umath, "exp", Flathead_impl::Math_Exp);
	FUNCTION_PROTOTYPE(umath, "findDeltaAngle", Flathead_impl::Math_FindDeltaAngle);
	FUNCTION_PROTOTYPE(umath, "radiansToDegrees", Flathead_impl::Math_RadiansToDegrees);
	FUNCTION_PROTOTYPE(umath, "degreesToRadians", Flathead_impl::Math_DegreesToRadians);
	FUNCTION_PROTOTYPE(umath, "unwindDegrees", Flathead_impl::Math_UnwindDegrees);
	FUNCTION_PROTOTYPE(umath, "unwindRadians", Flathead_impl::Math_UnwindRadians);

	globalTemplate->Set(String::NewFromUtf8(GetIsolate(), "UMath"), umath->GetFunction()->NewInstance(), ReadOnly);
}

void Flathead_impl::Math_Abs(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::Abs(value));
}

void Flathead_impl::Math_ACos(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::Acos(value));
}

void Flathead_impl::Math_ASin(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::Asin(value));
}

void Flathead_impl::Math_ATan(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::Atan(value));
}

void Flathead_impl::Math_ATan2(const FunctionCallbackInfo<Value>& args)
{
	double Y, X;

	HandleScope handle_scope(args.GetIsolate());

	Y = args[0]->NumberValue();
	X = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::Atan2(Y, X));
}

void Flathead_impl::Math_Ceil(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::CeilToInt(value));
}

void Flathead_impl::Math_Clamp(const FunctionCallbackInfo<Value>& args)
{
	double value, minimum, maximum;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();
	minimum = args[1]->NumberValue();
	maximum = args[2]->NumberValue();

	args.GetReturnValue().Set(FMath::Clamp<double>(value, minimum, maximum));
}

void Flathead_impl::Math_ClampAngle(const FunctionCallbackInfo<Value>& args)
{
	double value, minAngle, maxAngle;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();
	minAngle = args[1]->NumberValue();
	maxAngle = args[2]->NumberValue();

	args.GetReturnValue().Set(FMath::ClampAngle(value, minAngle, maxAngle));
}

void Flathead_impl::Math_Cos(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::Cos(value));
}

void Flathead_impl::Math_Exp(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::Exp(value));
}

void Flathead_impl::Math_FindDeltaAngle(const FunctionCallbackInfo<Value>& args)
{
	double angle1, angle2;

	HandleScope handle_scope(args.GetIsolate());

	angle1 = args[0]->NumberValue();
	angle2 = args[1]->NumberValue();

	args.GetReturnValue().Set(FMath::FindDeltaAngle(angle1, angle2));
}

void Flathead_impl::Math_RadiansToDegrees(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::RadiansToDegrees(value));
}

void Flathead_impl::Math_DegreesToRadians(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::DegreesToRadians(value));
}

void Flathead_impl::Math_UnwindRadians(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::UnwindRadians(value));
}

void Flathead_impl::Math_UnwindDegrees(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::UnwindDegrees(value));
}

void Flathead_impl::Math_FInterpConstantTo(const FunctionCallbackInfo<Value>& args)
{
	double current, target, delta, speed;

	HandleScope handle_scope(args.GetIsolate());

	current = args[0]->NumberValue();
	target = args[1]->NumberValue();
	delta = args[2]->NumberValue();
	speed = args[3]->NumberValue();

	args.GetReturnValue().Set(FMath::FInterpConstantTo(current, target, delta, speed));
}

void Flathead_impl::Math_FInterpTo(const FunctionCallbackInfo<Value>& args)
{
	double current, target, delta, speed;

	HandleScope handle_scope(args.GetIsolate());

	current = args[0]->NumberValue();
	target = args[1]->NumberValue();
	delta = args[2]->NumberValue();
	speed = args[3]->NumberValue();

	args.GetReturnValue().Set(FMath::FInterpTo(current, target, delta, speed));
}

void Flathead_impl::Math_FixedTurn(const FunctionCallbackInfo<Value>& args)
{
	double current, desired, rate;

	HandleScope handle_scope(args.GetIsolate());

	current = args[0]->NumberValue();
	desired = args[1]->NumberValue();
	rate = args[2]->NumberValue();

	args.GetReturnValue().Set(FMath::FixedTurn(current, desired, rate));
}

void Flathead_impl::Math_FloatSelect(const FunctionCallbackInfo<Value>& args)
{
	double comparand, GEZero, TZero;

	HandleScope handle_scope(args.GetIsolate());

	comparand = args[0]->NumberValue();
	GEZero = args[1]->NumberValue();
	TZero = args[2]->NumberValue();

	args.GetReturnValue().Set(FMath::FloatSelect(comparand, GEZero, TZero));
}

void Flathead_impl::Math_Floor(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::FloorToDouble(value));
}

void Flathead_impl::Math_Fmod(const FunctionCallbackInfo<Value>& args)
{
	double X, Y;

	HandleScope handle_scope(args.GetIsolate());

	X = args[0]->NumberValue();
	Y = args[1]->NumberValue();

	args.GetReturnValue().Set(FMath::Fmod(X, Y));
}

void Flathead_impl::Math_Fractional(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::Fractional(value));
}

void Flathead_impl::Math_FRand(const FunctionCallbackInfo<Value>& args)
{
	HandleScope handle_scope(args.GetIsolate());

	args.GetReturnValue().Set(FMath::FRand());
}

void Flathead_impl::Math_FRandRange(const FunctionCallbackInfo<Value>& args)
{
	double minimum, maximum;

	HandleScope handle_scope(args.GetIsolate());

	minimum = args[0]->NumberValue();
	maximum = args[1]->NumberValue();

	args.GetReturnValue().Set(FMath::FRandRange(minimum, maximum));
}

void Flathead_impl::Math_IsFinite(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::IsFinite(value));
}

void Flathead_impl::Math_IsNaN(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::IsNaN(value));
}

void Flathead_impl::Math_IsNearlyEqual(const FunctionCallbackInfo<Value>& args)
{
	double value1, value2, delta;

	HandleScope handle_scope(args.GetIsolate());

	value1 = args[0]->NumberValue();
	value2 = args[1]->NumberValue();
	delta = args[2]->NumberValue();

	args.GetReturnValue().Set(FMath::IsNearlyEqual(value1, value2, delta));
}

void Flathead_impl::Math_IsNearlyZero(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::IsNearlyZero(value));
}

void Flathead_impl::Math_IsPowerOfTwo(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::IsPowerOfTwo(value));
}

void Flathead_impl::Math_GridSnap(const FunctionCallbackInfo<Value>& args)
{
	double value, grid;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();
	grid = args[1]->NumberValue();

	args.GetReturnValue().Set(FMath::GridSnap(value, grid));
}

void Flathead_impl::Math_InvSqrt(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::InvSqrt(value));
}

void Flathead_impl::Math_InvSqrtEst(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::InvSqrtEst(value));
}

void Flathead_impl::Math_Log2(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::Log2(value));
}

void Flathead_impl::Math_Loge(const FunctionCallbackInfo<Value>& args)
{
	double value;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();

	args.GetReturnValue().Set(FMath::Loge(value));
}

void Flathead_impl::Math_LogX(const FunctionCallbackInfo<Value>& args)
{
	double value, base;

	HandleScope handle_scope(args.GetIsolate());

	value = args[0]->NumberValue();
	base = args[1]->NumberValue();

	args.GetReturnValue().Set(FMath::LogX(value, base));
}

void Flathead_impl::Math_MakePulsatingValue(const FunctionCallbackInfo<Value>& args)
{
	double time, pulses, phase;

	HandleScope handle_scope(args.GetIsolate());

	time = args[0]->NumberValue();
	pulses = args[1]->NumberValue();
	phase = args[2]->NumberValue();

	args.GetReturnValue().Set(FMath::MakePulsatingValue(time, pulses, phase));
}

void Flathead_impl::Math_Max(const FunctionCallbackInfo<Value>& args)
{
	double value1, value2;

	HandleScope handle_scope(args.GetIsolate());

	value1 = args[0]->NumberValue();
	value2 = args[1]->NumberValue();

	args.GetReturnValue().Set(FMath::Max<double>(value1, value2));
}

void Flathead_impl::Math_Min(const FunctionCallbackInfo<Value>& args)
{
	double value1, value2;

	HandleScope handle_scope(args.GetIsolate());

	value1 = args[0]->NumberValue();
	value2 = args[1]->NumberValue();

	args.GetReturnValue().Set(FMath::Min<double>(value1, value2));
}

void Flathead_impl::Math_Pow(const FunctionCallbackInfo<Value>& args)
{
	double value1, value2;

	HandleScope handle_scope(args.GetIsolate());

	value1 = args[0]->NumberValue();
	value2 = args[1]->NumberValue();

	args.GetReturnValue().Set(FMath::Pow(value1, value2));
}

void Flathead_impl::Math_Rand(const FunctionCallbackInfo<Value>& args)
{
	HandleScope handle_scope(args.GetIsolate());

	args.GetReturnValue().Set(FMath::Rand());
}

Handle<Context> Flathead_impl::GetGlobalContext()
{
	EscapableHandleScope handle_scope(GetIsolate());

	return handle_scope.Escape(Local<Context>::New(GetIsolate(), globalContext));
}

Handle<Object> Flathead_impl::Expose(AActor *actor, FString Name)
{
	// We will be creating temporary handles so we use a handle scope.
	EscapableHandleScope handle_scope(GetIsolate());

	Local<Context> context = Local<Context>::New(GetIsolate(), globalContext);
	Context::Scope ContextScope(context);

	Handle<ObjectTemplate> actor_templ = ObjectTemplate::New();  
	actor_templ->SetInternalFieldCount(1);

	// WrapActor(actor_templ);
	
	Local<Object> obj = actor_templ->NewInstance();
	obj->SetInternalField(0, External::New(GetIsolate(), actor));

	WrapActor(obj);

	context->Global()->Set(String::NewFromUtf8(GetIsolate(), TCHAR_TO_ANSI(*Name)), obj);

	return handle_scope.Escape(obj);
}

void Flathead_impl::WrapActor(Handle<Object> actor)
{
	actor->SetAccessor(String::NewFromUtf8(GetIsolate(), "creationTime", String::kInternalizedString), Flathead_impl::Actor_CreationTime);

	actor->Set(String::NewFromUtf8(GetIsolate(), "setActorPosition", String::kInternalizedString), FunctionTemplate::New(GetIsolate(), Flathead_impl::Actor_SetActorLocation)->GetFunction());
}

void Flathead_impl::Actor_CreationTime(Local<String> name, const PropertyCallbackInfo<Value>& info)
{
	Local<Object> self = info.Holder();
	Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
	void* ptr = wrap->Value();

	float value = static_cast<AActor*>(ptr)->CreationTime;

	info.GetReturnValue().Set(Number::New(info.GetIsolate(), value));
}

void Flathead_impl::Actor_SetActorLocation(const FunctionCallbackInfo<Value>& args)
{
	float x, y, z;

	Local<Object> self = args.Holder();
	Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
	void* ptr = wrap->Value();

	AActor *actor = static_cast<AActor*>(ptr);

	x = args[0]->NumberValue();
	y = args[1]->NumberValue();
	z = args[2]->NumberValue();

	args.GetReturnValue().Set(Boolean::New(args.GetIsolate(), actor->SetActorLocation(FVector(x, y, z))));
}

#pragma endregion

