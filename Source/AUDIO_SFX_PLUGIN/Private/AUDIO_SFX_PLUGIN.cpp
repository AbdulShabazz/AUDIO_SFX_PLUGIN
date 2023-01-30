// Copyright Epic Games, Inc. All Rights Reserved.

#include "AUDIO_SFX_PLUGIN.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include <GameFramework/Actor.h>
#include <Engine/Classes/Engine/Engine.h>
#include <Engine/World.h>
#include "AUDIO_SFX_PLUGINStyle.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include <stdexcept>

static const FName AUDIO_SFX_PLUGINTabName("AUDIO_SFX_PLUGIN");

#define LOCTEXT_NAMESPACE "FAUDIO_SFX_PLUGINModule"

bool FAUDIO_SFX_PLUGINModule::OnGeneratePerlinNoise()
{
    return true;
}

void FAUDIO_SFX_PLUGINModule::GeneratePerlinNoise()
{

}

void FAUDIO_SFX_PLUGINModule::FillMenu(FMenuBuilder& MenuBarBuilderRef)
{
    MenuBarBuilderRef.AddMenuEntry(
        FText::FromString("Perlin Noise"),
        FText::FromString("Generate Perlin Noise"),
        FSlateIcon(),
        FUIAction(
            FExecuteAction::CreateRaw(this, &FAUDIO_SFX_PLUGINModule::GeneratePerlinNoise),
            FCanExecuteAction::CreateRaw(this, &FAUDIO_SFX_PLUGINModule::OnGeneratePerlinNoise)
        )
    );
}

void FAUDIO_SFX_PLUGINModule::AddMenuBarExtension(FMenuBarBuilder& MenuBarBuilderRef)
{
    TAttribute<FText> inMenuLabelFText;
    inMenuLabelFText.Set(FText(LOCTEXT("WindowWidgetMenuText", "Tools")));

    TAttribute<FText> inMenuToolTipFText;
    inMenuLabelFText.Set(FText(LOCTEXT("WindowWidgetMenuText", "Provides channel-editing tools, features, and functionality")));

    MenuBarBuilderRef.AddPullDownMenu(
        inMenuLabelFText,
        inMenuToolTipFText,
        FNewMenuDelegate::CreateRaw(this, &FAUDIO_SFX_PLUGINModule::FillMenu)
    );
}

void FAUDIO_SFX_PLUGINModule::StartupModule()
{
    /** This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per module */
    
    FAUDIO_SFX_PLUGINStyle::Initialize();
    FAUDIO_SFX_PLUGINStyle::ReloadTextures();
    FAUDIO_SFX_PLUGINCommands::Register();

    TSharedPtr<FUICommandList> PluginCommands = MakeShareable(new FUICommandList);

    const FAUDIO_SFX_PLUGINCommands& CommandActions = FAUDIO_SFX_PLUGINCommands::Get();

    PluginCommands->MapAction(
        CommandActions.OpenPluginWindow,
        FExecuteAction::CreateRaw(this, &FAUDIO_SFX_PLUGINModule::PluginButtonClicked),
        FCanExecuteAction(), 
        FIsActionChecked());
    
    UToolMenus::RegisterStartupCallback(
        FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAUDIO_SFX_PLUGINModule::RegisterMenus));

    // Add (Toolbar) button to level editor submenu (eg. LevelEditor.MainMenu[.Window, .Tools, etc] in UToolMenus::RegisterStartupCallback(...)
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
        AUDIO_SFX_PLUGINTabName,
        FOnSpawnTab::CreateRaw(this, &FAUDIO_SFX_PLUGINModule::OnSpawnPluginTab)
    )
    .SetDisplayName(LOCTEXT("FAUDIO_SFX_PLUGINTabTitle", "AUDIO_SFX_PLUGIN"))
    .SetMenuType(ETabSpawnerMenuType::Enabled);
}

void FAUDIO_SFX_PLUGINModule::RegisterMenus()
{
    /** Owner will be used for cleanup in call to UToolMenus::UnregisterOwner */
    FToolMenuOwnerScoped OwnerScoped(this);

    const TSharedPtr<const FUICommandList> PluginCommands = MakeShareable(new FUICommandList);

    const FAUDIO_SFX_PLUGINCommands& CommandActions = FAUDIO_SFX_PLUGINCommands::Get();
    UToolMenu* MenuPtr = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
    FToolMenuSection& Section = MenuPtr->FindOrAddSection("AUDIO_SFX_PLUGIN.LevelEditor");
    Section.AddMenuEntryWithCommandList(CommandActions.OpenPluginWindow, PluginCommands);
}

void FAUDIO_SFX_PLUGINModule::FillToolBar()
{

}

void FAUDIO_SFX_PLUGINModule::ShutdownModule()
{
    /** 
    * This function may be called during shutdown to clean up your module.
    *   For modules that support dynamic reloading,
    *   we call this function before unloading the module.
    */
    UToolMenus::UnRegisterStartupCallback(this);
    UToolMenus::UnregisterOwner(this);
    FAUDIO_SFX_PLUGINStyle::Shutdown();
    FAUDIO_SFX_PLUGINCommands::Unregister();
    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AUDIO_SFX_PLUGINTabName);
}

/**
* Spawns the AUDIO_SFX_PLUGIN (nomad docktab) window. 
* Usage : TSharedRef<SDockTab> MyDockTabObjRef = OnSpawnPluginTab(SpawnTabArgs);
* 
* @param [ const FSpawnTabArgs& SpawnTabArgs ] --- The spawn params.
* @return [ TSharedRef<SDockTab> ] --- The slate window dockable tab.
*/
TSharedRef<SDockTab> FAUDIO_SFX_PLUGINModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
    TSharedRef<UMGViewportComponent> SNWin = SNew(UMGViewportComponent);
    UMGViewportComponent::FArguments InArgs;
    SNWin.Get().Construct(InArgs);
    TAttribute<FText> inAttributesTXT;
    FText WidgetLabel = FText(LOCTEXT("WindowWidgetText", "The Audio SFX Design Tool"));
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

// class UMGViewportComponent //

void UMGViewportComponent::GeneratePerlinNoiseMenuAPI()
{
    // 
}

void UMGViewportComponent::Construct(const FArguments& InArgs)
{
    this->SetTitle(FText::FromString(TEXT("The Audio SFX Design Tool")));    
    this->bCreateTitleBar = true;    
    FText ToolTipFText = FText::FromString(TEXT("The Audio SFX Design Tool"));    
    this->SetToolTipText(ToolTipFText);    
}

#undef LOCTEXT_NAMESPAC
    
IMPLEMENT_MODULE(FAUDIO_SFX_PLUGINModule, AUDIO_SFX_PLUGIN)