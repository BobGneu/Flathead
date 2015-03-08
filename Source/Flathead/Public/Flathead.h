// Copyright 2013 Gneu, LLC. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

#include "FlatheadCore.h"

/**
* The public interface to this module. 
*/
class Flathead : public IModuleInterface
{

public:

	static inline Flathead& Get()
	{
		return FModuleManager::LoadModuleChecked<Flathead>("Flathead");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("Flathead");
	}

	/**
	* Called right after the module DLL has been loaded and the module object has been created
	*/
	virtual void StartupModule()
	{
		LoadFHDLL();
	}

	/**
	* Called before the module is unloaded, right before the module object is destroyed.
	*/
	virtual void ShutdownModule()
	{
	}

	void LoadFHDLL()
	{

	}

	virtual bool LoadGameScript(FString fileName) = 0;
	virtual bool LoadGameScript(char* fileName) = 0;

	virtual bool Execute(FString data, FString filename) = 0;
	virtual bool Execute(char * data, char * filename) = 0;
};
