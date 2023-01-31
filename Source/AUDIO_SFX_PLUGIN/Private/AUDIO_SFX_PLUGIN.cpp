// Copyright Epic Games, Inc. All Rights Reserved.

#include "AUDIO_SFX_PLUGIN.h"

static const FName AUDIO_SFX_PLUGINTabName("AUDIO_SFX_PLUGIN");

#define LOCTEXT_NAMESPACE "FAUDIO_SFX_PLUGINModule"

void FAUDIO_SFX_PLUGINModule::FillToolBar()
{

}

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

TSharedRef<SWidget> FAUDIO_SFX_PLUGINModule::GetTabContent(const FName& TabID)
{
    TAttribute<FText> TabIDFText{ FText::Format(LOCTEXT("WindowWidgetText", "This is the content of tab '{0}'"), FText::FromString(TabID.ToString())) };
    return SNew(STextBlock)
        .Text(TabIDFText);
}

void FAUDIO_SFX_PLUGINModule::RegisterMenus()
{
    /** Owner will be used for cleanup in call to UToolMenus::UnregisterOwner */
    FToolMenuOwnerScoped OwnerScoped(this);

    const FAUDIO_SFX_PLUGINCommands& CommandActions = FAUDIO_SFX_PLUGINCommands::Get();

    {
        // Add menu to the 'Window' sub menu of the level editor
        UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
        {
            FToolMenuSection& Section = Menu->FindOrAddSection("Audio_Plugins.AUDIO_SFX_PLUGIN.LevelEditor");
            Section.AddMenuEntryWithCommandList(CommandActions.OpenPluginWindow, PluginCommands);
        }
    }

    {
        UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
        {
            FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
            {
                FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(CommandActions.OpenPluginWindow));
                Entry.SetCommandList(PluginCommands);
            }
        }
    }
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
    const FName TabName{ *FString::FromInt(TabCounterInt32++) + FString("_") + AUDIO_SFX_PLUGINTabName.ToString() };
        
    // Get an icon for our nomad tab //
    const ISlateStyle& Style = FAUDIO_SFX_PLUGINStyle::Get();
    FSlateIcon Icon{ Style.GetStyleSetName(), "AUDIO_SFX_PLUGIN.OpenPluginWindow" };

    FText WindowText = FText::Format(LOCTEXT("FAUDIO_SFX_PLUGINTabTitle", "{0}"), FText::FromString(TabName.ToString()));
    
    // Add a (Toolbar) button to level editor @submenu LevelEditor.MainMenu[.Window, .Tools, ..] 
    //   in UToolMenus::RegisterStartupCallback(...)
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
        TabName,
        FOnSpawnTab::CreateRaw(this, &FAUDIO_SFX_PLUGINModule::OnSpawnPluginTab)
    )
        .SetMenuType(ETabSpawnerMenuType::Enabled) // Hide this LevelEditor.MainMenu.Window button, we'll create our own...
        .SetIcon(Icon);
    
    const FTabId TabId{ TabName };
    TSharedPtr<SDockTab> CurrentTabPtr = FGlobalTabmanager::Get()->TryInvokeTab(TabId);
    TAttribute<FText> inAttributesTXT;
    FText WidgetLabel = FText::Format(LOCTEXT("WindowWidgetText", "The Audio SFX Design Tool [{0}]"), FText::FromString(*FString::FromInt(TabCounterInt32-1)));
    inAttributesTXT.Set(WidgetLabel);
    CurrentTabPtr->SetLabel(inAttributesTXT);
}

void FAUDIO_SFX_PLUGINModule::StartupModule()
{
    /** This code will execute after your module is loaded into memory;
    *   the exact timing is specified in the .uplugin file per module */

    FAUDIO_SFX_PLUGINStyle::Initialize();
    FAUDIO_SFX_PLUGINStyle::ReloadTextures();
    FAUDIO_SFX_PLUGINCommands::Register();

    PluginCommands = MakeShareable(new FUICommandList);

    const FAUDIO_SFX_PLUGINCommands& CommandActions = FAUDIO_SFX_PLUGINCommands::Get();

    PluginCommands->MapAction(
        CommandActions.OpenPluginWindow,
        FExecuteAction::CreateRaw(this, &FAUDIO_SFX_PLUGINModule::PluginButtonClicked),
        FCanExecuteAction(),
        FIsActionChecked());

    UToolMenus::RegisterStartupCallback(
        FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAUDIO_SFX_PLUGINModule::RegisterMenus));
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