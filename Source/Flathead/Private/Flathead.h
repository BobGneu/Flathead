// Copyright 2013 Gneu, LLC. All Rights Reserved.
//
// https://github.com/joyent/node/blob/master/lib/util.js#L618-L641
//
// SetRegisterMountPointDelegate
// v8 versioning: 0c4277f716384b56ba8cb6c505ee67625b16ecf7 3.26.0

#include "IFlathead.h"

#pragma once

class Flathead_impl : public Flathead
{

public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void SetIsolate(v8::Isolate* isolate)
	{
		_Isolate = isolate; 
	}

	v8::Isolate * GetIsolate()
	{
		return _Isolate;
	}

	v8::Handle<v8::Context> CreateGlobalContext();

	bool LoadGameScript(FString filename);
	bool Execute(FString data, FString filename); 

	bool LoadGameScript(char* filename);
	bool Execute(char * data, char * filename);

	v8::Handle<v8::Object> Expose(AActor *, FString);

	virtual v8::Handle<v8::Context> GetGlobalContext();

protected:

	v8::Persistent<v8::Context> globalContext;

	FString GetCoreScriptsDirectory();
	FString GetGameScriptsDirectory();

	bool LoadScript(char* fileName);
	bool LoadCoreScript(char* fileName);

	void WrapActor(v8::Local<v8::ObjectTemplate> actor_templ);

	void DefineGameFunctions(v8::Local<v8::ObjectTemplate> objTemplate);
	void DefineRequire(v8::Local<v8::ObjectTemplate> globalTemplate);
	void DefineMath(v8::Local<v8::ObjectTemplate> globalTemplate);
	void DefineActor(v8::Local<v8::ObjectTemplate> globalTemplate);
	void DefineUObject(v8::Local<v8::ObjectTemplate> globalTemplate);

	static FString ArgsToFstr(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void GetVersion(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);

	static void GetV8Version(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void GetBindingVersion(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	
	static void FatalCallback(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void ErrorCallback(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void WarningCallback(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void DisplayCallback(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void LogCallback(const v8::FunctionCallbackInfo<v8::Value>& info);

	static void LoggerCallback(const char* message, int status);

	static void Require(const v8::FunctionCallbackInfo<v8::Value>& info);

	static void Math_Abs(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_ACos(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_ASin(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_Clamp(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void Math_ATan(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_ATan2(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_Ceil(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_ClampAngle(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_Cos(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_Exp(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_FindDeltaAngle(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void Math_RadiansToDegrees(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_DegreesToRadians(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void Math_UnwindRadians(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_UnwindDegrees(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_Rand(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_Pow(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_Min(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_Max(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_MakePulsatingValue(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_LogX(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_Loge(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_Log2(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_InvSqrtEst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_InvSqrt(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_GridSnap(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_IsPowerOfTwo(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_IsNearlyZero(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_IsNearlyEqual(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_IsFinite(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_FRandRange(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_FRand(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_Fractional(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_Fmod(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_Floor(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_FloatSelect(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_FixedTurn(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_FInterpConstantTo(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_FInterpTo(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Math_IsNaN(const v8::FunctionCallbackInfo<v8::Value>& args);
	
	static void Actor_CreationTime(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void Actor_SetActorLocation(const v8::FunctionCallbackInfo<v8::Value>& args);
	v8::Isolate *_Isolate;

private:

	static Flathead_impl* accessor;
};

IMPLEMENT_MODULE(Flathead_impl, Flathead)
