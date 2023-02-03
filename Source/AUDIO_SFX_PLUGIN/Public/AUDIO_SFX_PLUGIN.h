// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


//#include "Tones.h"
#include "AUDIO_SFX_PLUGIN.HEADERS.h"

class UMGViewportComponent : public SWindow
{

public:

    SLATE_BEGIN_ARGS(UMGViewportComponent) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);
    void GeneratePerlinNoiseMenuAPI();
    
private:
    TObjectPtr<UWorld> World;
    TObjectPtr<ACameraActor> Camera;
    TObjectPtr<APlayerController> PlayerController;
    TObjectPtr<FViewportClient/*UGameViewportClient*/> ViewportClient;
    TObjectPtr<FViewport> Viewport;

};

static class MyGlobalTabManagerClass : public FGlobalTabmanager
{

public:
    virtual bool CanCloseManager(const TSet<TSharedRef<SDockTab>>& TabsToIgnore = TSet<TSharedRef<SDockTab>>()) override;

protected:
    virtual void OnTabForegrounded(const TSharedPtr<SDockTab>& NewForegroundTabPtr, const TSharedPtr<SDockTab>& BackgroundedTabPtr) override;
    virtual void OnTabRelocated(const TSharedRef<SDockTab>& RelocatedTabRef, const TSharedPtr<SWindow>& NewOwnerWindowPtr) override;
    virtual void OnTabClosing(const TSharedRef<SDockTab>& TabBeingClosedRef) override;
    virtual void UpdateStats() override;
    virtual void OpenUnmanagedTab(FName PlaceholderIdFname, const FSearchPreference& SearchPreferenceRef, const TSharedRef<SDockTab>& UnmanagedTabRef) override;
    virtual void FinishRestore() override;

public:
    virtual void OnTabManagerClosing() override;

};

class FAUDIO_SFX_PLUGINModule : public IModuleInterface
{
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    
    /** This function will be bound to Command (by default it will bring up plugin window) */
    void PluginButtonClicked();

public:
    TSharedRef<SWidget> GetTabContent(const FName& TabID);
    void GeneratePerlinNoise();
    bool OnGeneratePerlinNoise();
    void FillToolBar();
    void AddMenuBarExtension(FMenuBarBuilder&);
    void FillMenu(FMenuBuilder&);
    
private:
    int32 DebugInt32 = 0;
    int32 TabCounterInt32 = 1;
    void RegisterMenus();

protected:
    TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
    TSharedPtr<class FUICommandList> PluginCommands;

};