// Copyright Epic Games, Inc. All Rights Reserved.

#include "AUDIO_SFX_PLUGIN.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include <GameFramework/Actor.h>
#include <Engine/Classes/Engine/Engine.h>
#include <Engine/World.h>
#include "AUDIO_SFX_PLUGINStyle.h"
#include "AUDIO_SFX_PLUGINCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include <stdexcept>
//#include <Widgets/SWindow.h>
//#include <Engine/Classes/Engine/GameInstance.h>
//#include <Engine/GameViewportClient.h>
//#include <Windows.h>
//#include <Editor/UnrealEd/Public/EditorViewportClient.h>
//#include "DXRApplication.h"

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

/**
* Spawns the AUDIO_SFX_PLUGIN (tab) window. 
* Usage : TSharedRef<SDockTab> MyDockTabObjPtr = OnSpawnPluginTab(SpawnTabArgs);
* @header AUDIOSFX_PLUGIN.h
* @param [ const FSpawnTabArgs& SpawnTabArgs ] --- The spawn params.
* @return [ TSharedRef<SDockTab> ] --- The window slate dock tab object.
*/
TSharedRef<SDockTab> FAUDIO_SFX_PLUGINModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
    TSharedRef<UMGViewportComponent> SNWin = SNew(UMGViewportComponent);

    UMGViewportComponent::FArguments InArgs;

    SNWin.Get().Construct(InArgs);

    TAttribute<FText> inAttributesTXT;

    FText WidgetLabel = FText(
        LOCTEXT("WindowWidgetText", "The Audio SFX Design Tool")
    );

    inAttributesTXT.Set(WidgetLabel);

    return SNew(SDockTab)
        .TabRole(ETabRole::MajorTab)
        .Label(inAttributesTXT)
        [
            SNWin
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

void UMGViewportComponent::Construct(const FArguments& InArgs)
{
    this->SetTitle(FText::FromString(TEXT("The Audio SFX Designer")));

    this->bCreateTitleBar = true; 
    
    FText TTip = FText::FromString(
        TEXT("The Audio SFX Design Tool")
    );
    this->SetToolTipText(TTip);
}

TSharedPtr<UMGViewportComponent> UMGViewportComponent::toSharedPtr()
{
    return TSharedPtr<UMGViewportComponent>();
}
