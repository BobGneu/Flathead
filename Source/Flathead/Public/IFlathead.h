// Copyright 2013 Gneu, LLC. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

// Disable warning messages 4946 - reinterpret_cast of similar type
// This is done to allow for v8 Initialization 
#pragma warning( push )
#pragma warning( disable : 4946 )

#include "v8.h"

// Resume standard warnings
#pragma warning( pop )

/**
* The public interface to this module. 
*/
class IFlathead : public IModuleInterface
{

public:

	static inline IFlathead& Get()
	{
		return FModuleManager::LoadModuleChecked<IFlathead>("Flathead");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("Flathead");
	}

	virtual v8::Isolate * GetIsolate() = 0;
	virtual v8::Handle<v8::Context> GetGlobalContext() = 0;

	virtual	v8::Handle<v8::Object> Expose(AActor *actorToExpose, FString name) = 0;

	virtual bool LoadGameScript(FString fileName) = 0;
	virtual bool LoadGameScript(char* fileName) = 0;

	virtual bool Execute(FString data, FString filename) = 0;
	virtual bool Execute(char * data, char * filename) = 0;
};
