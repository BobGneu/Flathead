// Copyright 2013 Gneu, LLC. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

#include "FlatheadCore.h"

/**
* The public interface to this module. 
*/
class FlatheadModule : public IModuleInterface
{
public:

	void StartupModule();
	void ShutdownModule();

	int LoadFHDLL();
	void ReleaseFHDLL();

	void* FlatheadDLLHandle;
};

IMPLEMENT_MODULE(FlatheadModule, FlatheadM);
