// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "Tones.h"
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

class FAUDIO_SFX_PLUGINModule : public IModuleInterface
{

public:

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
    int32 TabCounterInt32 = 0;
    void RegisterMenus();
    TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
    TSharedPtr<class FUICommandList> PluginCommands;

};