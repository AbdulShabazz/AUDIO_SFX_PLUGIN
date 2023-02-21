// Copyright Epic Games, Inc. All Rights Reserved.

// Unreal Engine 5 (local)
#include "TheAudio__TheAudioSfxPlugin.h"
#include "TheAudio__TheAudioSfxPluginStyle.h"
#include "TheAudio__TheAudioSfxPluginCommands.h"
//#include "UE5.DeclarativeSyntaxSupport.h"
//#include "UE5.EnumClass.h"

// Unreal Engine 5 (global)
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

// Unreal Engine 5 (plugin)
#include "AudioEqualization.h"
#include "AudioMix.h"
#include "AudioSummation.h"
#include "BlackNoise.h"
#include "BlueNoise.h"
#include "BluesteinFFT.h"
#include "ConvolutionReverb.h"
#include "CooleyTukeyFFT.h"
#include "FractalNoise.h"
#include "GreyNoise.h"
#include "includes.generated.h"
#include "KarplusStrongDelayLineSynthesis.h"
#include "Midi.generated.h"
#include "Midi.h"
#include "nlp.generated.h"
#include "nlp.h"
#include "nlp.ipa.dictionary.h"
#include "PinkNoise.h"
#include "PlateReverb.h"
#include "PurpleNoise.h"
#include "Radix2FFT.h"
#include "WaveEquation.h"
#include "WhiteNoise.h"
#include "WhitePerlinNoise.h"
#include "SimplexNoise.h"
#include "SpringReverb.h"
#include "TimeStretch.h"

// Generated includes
#include "sfx_ACOUSTIC.h"
#include "sfx_AIRPORT.h"
#include "sfx_BANK.h"
#include "sfx_BIOLOGICAL.h"
#include "sfx_BLANK.h"
#include "sfx_CAMERA.h"
#include "sfx_CARTOON.h"
#include "sfx_CHARGING.h"
#include "sfx_CONSTRUCTION.h"
#include "sfx_CROWD.h"
#include "sfx_DESTRUCTION.h"
#include "sfx_error.h"
#include "sfx_EXPLOSION.h"
#include "sfx_FIRE.h"
#include "sfx_FLUID.h"
#include "sfx_FOREST.h"
#include "sfx_GUN.h"
#include "sfx_HILLS.h"
#include "sfx_HOSPITAL.h"
#include "sfx_INDIE.h"
#include "sfx_JUNGLE.h"
#include "sfx_LAW.h"
#include "sfx_LAWNCARE.h"
#include "sfx_METALLIC.h"
#include "sfx_MOUNTAINS.h"
#include "sfx_MOVIE.h"
#include "sfx_NATURE.h"
#include "sfx_OFFICE.h"
#include "sfx_ORCHESTRAL.h"
#include "sfx_ORGANIC.h"
#include "sfx_PAPER.h"
#include "sfx_PLASTICS.h"
#include "sfx_POLAR.h"
#include "sfx_ROAD.h"
#include "sfx_SAVANNAH.h"
#include "sfx_SCI.h"
#include "sfx_SIREN.h"
#include "sfx_SPACE.h"
#include "sfx_STATIC.h"
#include "sfx_SWAMP.h"
#include "sfx_TAIGA.h"
#include "sfx_TRAFFIC.h"
#include "sfx_TRAILER.h"
#include "sfx_TUNDRA.h"
#include "sfx_VEHICLE.h"
#include "sfx_WAR.h"
#include "sfx_WEATHER.h"
#include "sfx_WOOD.h"
#include "sfx_WOODLANDS.h"
//#include "Tones.Default.Settings.h"
//#include "Tones.h"

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
	trace_a.push("FTheAudio__TheAudioSfxPluginModule::OnSpawnPluginTab");

	TSharedRef<UMGViewportComponent> SNWin = SNew(UMGViewportComponent);
	UMGViewportComponent::FArguments InArgs;

	SNWin.Get().Construct(InArgs);
	TAttribute<FText> inAttributesTXT;
	FText WidgetLabel = FText::Format(LOCTEXT("WindowWidgetText", "[{0}] - The Audio - The Audio SFX Plugin "), TabIndexInt8);
	inAttributesTXT.Set(WidgetLabel);

	trace_a.pop();

	return SNew(SDockTab)
		.TabRole(ETabRole::MajorTab)
		.Label(inAttributesTXT)
		[
			SNWin
		];

}

void FTheAudio__TheAudioSfxPluginModule::PluginButtonClicked()
{

	trace_a.push("FTheAudio__TheAudioSfxPluginModule::PluginButtonClicked");

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

	trace_a.pop();

}

void FTheAudio__TheAudioSfxPluginModule::RegisterMenus()
{
	trace_a.push("FTheAudio__TheAudioSfxPluginModule::RegisterMenus");

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

	trace_a.pop();
}

void FTheAudio__TheAudioSfxPluginModule::StartupModule()
{
	trace_a.push("FTheAudio__TheAudioSfxPluginModule::StartupModule");

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

	trace_a.pop();
}

void FTheAudio__TheAudioSfxPluginModule::ShutdownModule()
{
	trace_a.push("FTheAudio__TheAudioSfxPluginModule::ShutdownModule");

	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTheAudio__TheAudioSfxPluginStyle::Shutdown();

	FTheAudio__TheAudioSfxPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FTheAudio__TheAudioSfxPluginTabName);

	trace_a.pop();
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
