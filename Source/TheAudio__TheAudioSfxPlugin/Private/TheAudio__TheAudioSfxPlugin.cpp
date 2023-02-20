// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheAudio__TheAudioSfxPlugin.h"
#include "TheAudio__TheAudioSfxPluginStyle.h"
#include "TheAudio__TheAudioSfxPluginCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName FTheAudio__TheAudioSfxPluginTabName("TheAudio__TheAudioSfxPlugin");

#define LOCTEXT_NAMESPACE "FTheAudio__TheAudioSfxPluginModule"

/**
* Spawns the AUDIO_SFX_PLUGIN (nomad docktab) window.
* Usage : TSharedRef<SDockTab> MyDockTabObjRef = OnSpawnPluginTab(SpawnTabArgs);
*
* @param [ const FSpawnTabArgs& SpawnTabArgs ] --- The spawn params { const SWindow&, FTabId }.
* @return [ TSharedRef<SDockTab> ] --- The slate window dockable tab.
*/
TSharedRef<SDockTab> FTheAudio__TheAudioSfxPluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{

	TSharedRef<UMGViewportComponent> SNWin = SNew(UMGViewportComponent);
	UMGViewportComponent::FArguments InArgs;

	SNWin.Get().Construct(InArgs);
	TAttribute<FText> inAttributesTXT;
	FText WidgetLabel = FText::Format(LOCTEXT("WindowWidgetText", "[{0}] - The Audio - The Audio SFX Plugin "), TabIndexInt8);
	inAttributesTXT.Set(WidgetLabel);

	return SNew(SDockTab)
		.TabRole(ETabRole::MajorTab)
		.Label(inAttributesTXT)
		[
			SNWin
		];

}

void FTheAudio__TheAudioSfxPluginModule::PluginButtonClicked()
{

	TabIndexInt8 = TabCounterInt8++;
	const FName TabId{ *FString::FromInt(TabIndexInt8) + FString("-") + FTheAudio__TheAudioSfxPluginTabName.ToString() };

	// Get an icon for our nomad tab //
	const ISlateStyle& Style = FTheAudio__TheAudioSfxPluginStyle::Get();
	FSlateIcon Icon{ Style.GetStyleSetName(), "TheAudio__TheAudioSfxPlugin.OpenPluginWindow" };

	// Register a nomad tab spawner group container, and add an enabled OnSpawnPluginTab toolbar button to the LevelEditor.MainMenu.Window UE editor menu
	MyGlobalTabManagerClass::Get()->RegisterNomadTabSpawner(
		TabId,
		FOnSpawnTab::CreateRaw(this, &FTheAudio__TheAudioSfxPluginModule::OnSpawnPluginTab))
			.SetMenuType(ETabSpawnerMenuType::Enabled)
			.SetIcon(Icon);

	// Create the window //
	FSpawnTabArgs SpawnTabArgs{ SNew(UMGViewportComponent), TabId };
	FTheAudio__TheAudioSfxPluginModule::OnSpawnPluginTab(SpawnTabArgs);

	// Show the window //
	TSharedPtr<SDockTab> CurrentTabPtr = MyGlobalTabManagerClass::Get()->TryInvokeTab(TabId);

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

}

void FTheAudio__TheAudioSfxPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTheAudio__TheAudioSfxPluginStyle::Shutdown();

	FTheAudio__TheAudioSfxPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FTheAudio__TheAudioSfxPluginTabName);
}

bool MyGlobalTabManagerClass::CanCloseManager(const TSet<TSharedRef<SDockTab>>& TabsToIgnore)
{
	return FGlobalTabmanager::CanCloseManager(TabsToIgnore);
}

void MyGlobalTabManagerClass::OnTabForegrounded(const TSharedPtr<SDockTab>& NewForegroundTabPtr, const TSharedPtr<SDockTab>& BackgroundedTabPtr)
{
	FGlobalTabmanager::OnTabForegrounded(NewForegroundTabPtr, BackgroundedTabPtr);
}

void MyGlobalTabManagerClass::OnTabRelocated(const TSharedRef<SDockTab>& RelocatedTabRef, const TSharedPtr<SWindow>& NewOwnerWindowPtr)
{
	FGlobalTabmanager::OnTabRelocated(RelocatedTabRef, NewOwnerWindowPtr);
}

void MyGlobalTabManagerClass::OnTabClosing(const TSharedRef<SDockTab>& TabBeingClosedRef)
{
	//TabBeingClosedRef.Get();
	FGlobalTabmanager::OnTabClosing(TabBeingClosedRef);
}

void MyGlobalTabManagerClass::UpdateStats()
{
	FGlobalTabmanager::UpdateStats();
}

void MyGlobalTabManagerClass::OpenUnmanagedTab(FName PlaceholderIdFname, const FSearchPreference& SearchPreferenceRef, const TSharedRef<SDockTab>& UnmanagedTabRef)
{
	FGlobalTabmanager::OpenUnmanagedTab(PlaceholderIdFname, SearchPreferenceRef, UnmanagedTabRef);
}

void MyGlobalTabManagerClass::FinishRestore()
{
	FGlobalTabmanager::FinishRestore();
}

void MyGlobalTabManagerClass::OnTabManagerClosing()
{
	FGlobalTabmanager::OnTabManagerClosing();
}

void UMGViewportComponent::Construct(const FArguments& InArgs)
{
	this->SetTitle(FText::FromString(TEXT("The Audio - The Audio SFX Plugin")));
	this->bCreateTitleBar = true;
	FText ToolTipFText = FText::FromString(TEXT("The Audio - The Audio SFX Plugin"));
	this->SetToolTipText(ToolTipFText);
}

void UMGViewportComponent::GeneratePerlinNoiseMenuAPI()
{

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTheAudio__TheAudioSfxPluginModule, TheAudio__TheAudioSfxPlugin)
