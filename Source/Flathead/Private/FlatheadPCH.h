// Copyright 2013 Gneu, LLC. All Rights Reserved.

#pragma once;

#include "Engine.h"

// Disable warning messages 4946 - reinterpret_cast of similar type
// This is done to allow for v8 Initialization 
#pragma warning( push )
#pragma warning( disable : 4946 )

#include "v8.h"

// Resume standard warnings
#pragma warning( pop )

DECLARE_LOG_CATEGORY_EXTERN(FH, Log, All);

// You should place include statements to your module's private header files here.  You only need to
// add includes for headers that are used in most of your module's source files though.
