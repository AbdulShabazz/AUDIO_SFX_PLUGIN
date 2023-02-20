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

	//const FName TabName{ *FString::FromInt(TabCounterInt8++) + FString("_") + FTheAudio__TheAudioSfxPluginTabName.ToString() };

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTheAudio__TheAudioSfxPluginModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FTheAudio__TheAudioSfxPluginTabName, FOnSpawnTab::CreateRaw(this, &FTheAudio__TheAudioSfxPluginModule::OnSpawnPluginTab))
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

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FTheAudio__TheAudioSfxPluginTabName);
}


/**
* Spawns the AUDIO_SFX_PLUGIN (nomad docktab) window.
* Usage : TSharedRef<SDockTab> MyDockTabObjRef = OnSpawnPluginTab(SpawnTabArgs);
*
* @param [ const FSpawnTabArgs& SpawnTabArgs ] --- The spawn params.
* @return [ TSharedRef<SDockTab> ] --- The slate window dockable tab.
*/
TSharedRef<SDockTab> FTheAudio__TheAudioSfxPluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<UMGViewportComponent> SNWin = SNew(UMGViewportComponent);
	UMGViewportComponent::FArguments InArgs;

	SNWin.Get().Construct(InArgs);
	TAttribute<FText> inAttributesTXT;
	FText WidgetLabel = FText(LOCTEXT("WindowWidgetText", "The Audio - The Audio SFX Plugin"));
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
	//FGlobalTabmanager::Get()->TryInvokeTab(FTheAudio__TheAudioSfxPluginTabName);

	const FName TabName{ *FString::FromInt(TabCounterInt8++) + FString("_") + FTheAudio__TheAudioSfxPluginTabName.ToString() };

	// Get an icon for our nomad tab //
	const ISlateStyle& Style = FTheAudio__TheAudioSfxPluginStyle::Get();
	FSlateIcon Icon{ Style.GetStyleSetName(), "TheAudio__TheAudioSfxPlugin.OpenPluginWindow" };

	FText WindowText = FText::Format(LOCTEXT("TheAudio__TheAudioSfxPluginTabTitle", "{0}"), FText::FromString(TabName.ToString()));

	// Add a (Toolbar) button to level editor @submenu LevelEditor.MainMenu[.Window, .Tools, ..] 
	//   in UToolMenus::RegisterStartupCallback(...)
	MyGlobalTabManagerClass::Get()->RegisterNomadTabSpawner(
		TabName,
		FOnSpawnTab::CreateRaw(this, &FTheAudio__TheAudioSfxPluginModule::OnSpawnPluginTab)
	)
	.SetMenuType(ETabSpawnerMenuType::Hidden) // Hide the LevelEditor.MainMenu.Window toolbar button for now; we'll create our own...
	.SetIcon(Icon);

	const FTabId TabId{ TabName };
	TSharedPtr<SDockTab> CurrentTabPtr = MyGlobalTabManagerClass::Get()->TryInvokeTab(TabId);
	TAttribute<FText> inAttributesTXT;
	FText WidgetLabel = FText::Format(LOCTEXT("WindowWidgetText", "The Audio - SFX Design Tool [{0}]"), FText::FromString(*FString::FromInt(TabCounterInt8 - 1)));
	inAttributesTXT.Set(WidgetLabel);
	CurrentTabPtr->SetLabel(inAttributesTXT);
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
