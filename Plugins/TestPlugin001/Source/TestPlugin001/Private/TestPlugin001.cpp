// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestPlugin001.h"

#define LOCTEXT_NAMESPACE "FTestPlugin001Module"

void FTestPlugin001Module::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FTestPlugin001Module::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

FString FTestPlugin001Module::GetHelloWorld()
{
	return TEXT("Hello!!!");
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTestPlugin001Module, TestPlugin001)