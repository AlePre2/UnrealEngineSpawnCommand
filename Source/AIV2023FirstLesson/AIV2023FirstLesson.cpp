// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIV2023FirstLesson.h"
#include "Modules/ModuleManager.h"
#include "Misc/FileHelper.h"
#include "ContentBrowserModule.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "ContentBrowser/Public/IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"
#include "AssetRegistryModule.h"
#include "AssetData.h"
#include "AssetRegistry/AssetData.h"
#include "Editor.h"
#include "Dummy003.h"
#include "TestPlugin001.h"

DEFINE_LOG_CATEGORY(LogAIV);



bool operator<(const FModuleStatus& ModuleA, const FModuleStatus& ModuleB)
{
	return ModuleA.Name < ModuleB.Name;
}

class FAIVGameModule : public FDefaultGameModuleImpl, public FSelfRegisteringExec
{
public:
	virtual void StartupModule() override
	{
		//UE_LOG(LogAIV, Fatal, TEXT("Hello AIV 2"));

		FTestPlugin001Module& Module001 = FModuleManager::LoadModuleChecked<FTestPlugin001Module>("TestPlugin001");

		Module001.GetHelloWorld();

		FDummy003Module::HelloWorld();
		//FString Message = TEXT("Hello水Test水");

		//FFileHelper::SaveStringToFile(Message, TEXT("D:/simplestring.txt"));
		/*TArray<FModuleStatus> ModuleStatuses;
		FModuleManager::Get().QueryModules(ModuleStatuses);

		ModuleStatuses.Sort();

		TArray<FModuleStatus> ModuleStatuses2 = ModuleStatuses;

		TArray<int32, TInlineAllocator<5>> Hello;
		Hello.Add(1);
		Hello.Add(1);
		Hello.Add(1);
		Hello.Add(1);
		Hello.Add(1);
		Hello.Add(1);

		//for(int32 Index = 0; Index < ModuleStatuses.Num(); Index++)
		for (const FModuleStatus& ModuleStatus : ModuleStatuses)
		{
			UE_LOG(LogTemp, Error, TEXT("Module: %s %s"), *ModuleStatus.FilePath, *ModuleStatus.Name);
		}
		UE_LOG(LogTemp, Warning, TEXT("Hello World from AIV module"));


		FString Hello3 = UTF8_TO_TCHAR("hello");

		Hello3[2] = 'x';

		Hello3.Equals("ciao");

		//TCHAR* Hello2 = UTF8_TO_TCHAR("hello");
		//FModuleStatus* ModuleStatuses2 = ModuleStatuses.GetData();*/
	}

	virtual void ShutdownModule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("Goodbye from AIV module"));
	}

	virtual bool SupportsDynamicReloading() override
	{
		return false;
	}

	virtual bool Exec(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar)
	{

		if (FParse::Command(&Cmd, TEXT("SpawnSelectedActor")))
		{

			// Parse the value string
			int32 Amount = 0;
			FParse::Value(Cmd, TEXT("Amount="), Amount);

			// Get the selected assets
			GetSelectedAssets(Amount);

			TArray<FModuleStatus> ModuleStatuses;
			FModuleManager::Get().QueryModules(ModuleStatuses);

			/*GetSelectedAssets(5);*/

			ModuleStatuses.Sort();

			for (const FModuleStatus& ModuleStatus : ModuleStatuses)
			{
				if (ModuleStatus.Name.StartsWith(Cmd))
				{
					Ar.Logf(TEXT("Module: %s %s"), *ModuleStatus.FilePath, *ModuleStatus.Name);
				}
			}
			
			return true;
		}
		return false;
	}
};



void GetSelectedAssets(int amount)
{

	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");


	// Get the selected assets in the content browser
	TArray<FAssetData> SelectedAssets;
	ContentBrowserModule.Get().GetSelectedAssets(SelectedAssets);

	// Get a reference to the current world
	UWorld* World = nullptr;
	for (const FWorldContext& Context : GEngine->GetWorldContexts())
	{
		if (Context.WorldType == EWorldType::Editor)
		{
			World = Context.World();
			break;
		}
	}

	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get current world"));
		return;
	}


	    // Loop through the selected assets
    for (const FAssetData& AssetData : SelectedAssets)
    {
        // Check if the asset is a Blueprint child of AActor
		if (AssetData.GetClass()->IsChildOf(UBlueprint::StaticClass()))
        {
            // Log the name of the selected asset
            

			// Load the blueprint asset
			UBlueprint* BlueprintAsset = LoadObject<UBlueprint>(nullptr, *AssetData.ObjectPath.ToString());

			// Get the generated class of the Blueprint
			UClass* GeneratedClass = BlueprintAsset->GeneratedClass;	

			if (amount !=  0)
			{
				for (int i = 0; i < amount; i++) {
					World->SpawnActor<AActor>(GeneratedClass);
					// Code to execute in each iteration
				}
				UE_LOG(LogTemp, Log, TEXT("Multiple blueprint spawned: %s Amount %d"), *AssetData.AssetName.ToString(), amount);
			}
			else
			{
				World->SpawnActor<AActor>(GeneratedClass);
				UE_LOG(LogTemp, Log, TEXT("Blueprint spawned: %s"), *AssetData.AssetName.ToString());
			}

			// Spawn an instance of the actor in the current world
			


        }
		else
		{
			// Log the name of the selected asset
			UE_LOG(LogTemp, Log, TEXT("This is not a blueprint"));
		}
    }

}
IMPLEMENT_PRIMARY_GAME_MODULE(FAIVGameModule, AIV2023FirstLesson, "AIV2023FirstLesson");
