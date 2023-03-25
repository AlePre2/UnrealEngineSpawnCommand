// Copyright Geodesic Games, Inc. All Rights Reserved.

#include "Dummy003.h"

void FDummy003Module::StartupModule()
{

}

void FDummy003Module::ShutdownModule()
{
}

void FDummy003Module::HelloWorld()
{
	UE_LOG(LogTemp, Error, TEXT("HelloWorld"));
}

IMPLEMENT_MODULE(FDummy003Module, Dummy003);
