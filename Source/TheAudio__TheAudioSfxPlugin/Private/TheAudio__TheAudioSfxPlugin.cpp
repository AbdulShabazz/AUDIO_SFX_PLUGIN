// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheAudio__TheAudioSfxPlugin.h"
#include "TheAudio__TheAudioSfxPluginStyle.h"
#include "TheAudio__TheAudioSfxPluginCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName TheAudio__TheAudioSfxPluginTabName("TheAudio__TheAudioSfxPlugin");

#define LOCTEXT_NAMESPACE "FTheAudio__TheAudioSfxPluginModule"

void FTheAudio__TheAudioSfxPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTheAudio__TheAudioSfxPluginStyle::Initialize();
	FTheAudio__TheAudioSfxPluginStyle::ReloadTextures();

	FTheAudio__TheAudioSfxPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTheAudio__TheAudioSfxPluginCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FTheAudio__TheAudioSfxPluginModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTheAudio__TheAudioSfxPluginModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TheAudio__TheAudioSfxPluginTabName, FOnSpawnTab::CreateRaw(this, &FTheAudio__TheAudioSfxPluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FTheAudio__TheAudioSfxPluginTabTitle", "TheAudio__TheAudioSfxPlugin"))
		.SetMenuType(ETabSpawnerMenuType::Enabled);
}

void FTheAudio__TheAudioSfxPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTheAudio__TheAudioSfxPluginStyle::Shutdown();

	FTheAudio__TheAudioSfxPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TheAudio__TheAudioSfxPluginTabName);
}

TSharedRef<SDockTab> FTheAudio__TheAudioSfxPluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FTheAudio__TheAudioSfxPluginModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("TheAudio__TheAudioSfxPlugin.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FTheAudio__TheAudioSfxPluginModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(TheAudio__TheAudioSfxPluginTabName);
}

void FTheAudio__TheAudioSfxPluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTheAudio__TheAudioSfxPluginCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTheAudio__TheAudioSfxPluginCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTheAudio__TheAudioSfxPluginModule, TheAudio__TheAudioSfxPlugin)