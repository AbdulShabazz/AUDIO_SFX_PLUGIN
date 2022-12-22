// Copyright Epic Games, Inc. All Rights Reserved.

#include "AUDIO_SFX_PLUGIN.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include <GameFramework/Actor.h>
#include <GameFramework/PlayerController.h>
#include <Engine/Classes/Engine/Engine.h>
#include <Engine/World.h>
#include "AUDIO_SFX_PLUGINStyle.h"
#include "AUDIO_SFX_PLUGINCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
//#include <Editor/UnrealEd/Public/EditorViewportClient.h>
//#include "DXRApplication.h"

//class FSMy3DViewport : public FEditorViewportClient
//{
//public:
//    FSMy3DViewport() 
//    {
//
//    };
//} SMy3DViewport;

static const FName AUDIO_SFX_PLUGINTabName("AUDIO_SFX_PLUGIN");

#define LOCTEXT_NAMESPACE "FAUDIO_SFX_PLUGINModule"

void FAUDIO_SFX_PLUGINModule::StartupModule()
{
    // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    
    FAUDIO_SFX_PLUGINStyle::Initialize();
    FAUDIO_SFX_PLUGINStyle::ReloadTextures();

    FAUDIO_SFX_PLUGINCommands::Register();
    
    PluginCommands = MakeShareable(new FUICommandList);

    PluginCommands->MapAction(
        FAUDIO_SFX_PLUGINCommands::Get().OpenPluginWindow,
        FExecuteAction::CreateRaw(this, &FAUDIO_SFX_PLUGINModule::PluginButtonClicked),
        FCanExecuteAction()
    );

    UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAUDIO_SFX_PLUGINModule::RegisterMenus));
    
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
        AUDIO_SFX_PLUGINTabName, 
        FOnSpawnTab::CreateRaw(this, &FAUDIO_SFX_PLUGINModule::OnSpawnPluginTab)
    )
    .SetDisplayName(LOCTEXT("FAUDIO_SFX_PLUGINTabTitle", "AUDIO_SFX_PLUGIN"))
    .SetMenuType(ETabSpawnerMenuType::Hidden);

    //// Create a 3D viewport
    //GEngine->GameViewport->AddViewportWidgetContent(
    //    SNew(SMy3DViewport).AddMetaData<FTagMetaData>(FTagMetaData(TEXT("MyViewport")))
    //);

    //// Create a camera actor
    //FActorSpawnParameters SpawnParams;
    //SpawnParams.Name = TEXT("MyCamerActor");
    //TObjectPtr<ACameraActor> CameraActor = GEngine->GetWorld()->SpawnActor<ACameraActor>(FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
    //CameraActor->SetActorLabel(TEXT("MyCameraActor"));
    //
    //// Set the camera actor as the current player controller's controlled camera
    //TObjectPtr<APlayerController> PlayerController = GEngine->GetFirstLocalPlayerController(GEngine->GetWorld());
    //PlayerController->SetViewTarget(CameraActor);
}

void FAUDIO_SFX_PLUGINModule::ShutdownModule()
{
    // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
    // we call this function before unloading the module.

    UToolMenus::UnRegisterStartupCallback(this);

    UToolMenus::UnregisterOwner(this);

    FAUDIO_SFX_PLUGINStyle::Shutdown();

    FAUDIO_SFX_PLUGINCommands::Unregister();

    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AUDIO_SFX_PLUGINTabName);
    
    // Destroy the 3D viewport widget
   /* GEngine->GameViewport->RemoveViewportWidgetContent(
        SNew(SMy3DViewport).AddMetaData<FTagMetaData>(FTagMetaData(TEXT("MyViewport")))
    );*/
}

TSharedRef<SDockTab> FAUDIO_SFX_PLUGINModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
    //DXRApplication THE_RTX_APP;

    FText WidgetText = FText::Format(
        LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
        FText::FromString(TEXT("FAUDIO_SFX_PLUGINModule::OnSpawnPluginTab")),
        FText::FromString(TEXT("AUDIO_SFX_PLUGIN.cpp"))
        );

    return SNew(SDockTab)
        .TabRole(ETabRole::MajorTab)
        [
            // Put your tab content here!
            //SNew(SViewport)
            /*SNew(SBox)
            .HAlign(HAlign_Fill)
            .VAlign(VAlign_Fill)
            [
                SNew(SViewport)
            ]*/

            //SNew(SMy3DViewport)
            
            SNew(SBox)
            .HAlign(HAlign_Center)
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock)
                .Text(WidgetText)
            ]
        ];
}

void FAUDIO_SFX_PLUGINModule::PluginButtonClicked()
{
    FGlobalTabmanager::Get()->TryInvokeTab(AUDIO_SFX_PLUGINTabName);
}

void FAUDIO_SFX_PLUGINModule::RegisterMenus()
{
    // Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
    FToolMenuOwnerScoped OwnerScoped(this);

    {
        UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
        {
            FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
            Section.AddMenuEntryWithCommandList(FAUDIO_SFX_PLUGINCommands::Get().OpenPluginWindow, PluginCommands);
        }
    }

    {
        UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
        {
            FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
            {
                FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAUDIO_SFX_PLUGINCommands::Get().OpenPluginWindow));
                Entry.SetCommandList(PluginCommands);
            }
        }
    }
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FAUDIO_SFX_PLUGINModule, AUDIO_SFX_PLUGIN)