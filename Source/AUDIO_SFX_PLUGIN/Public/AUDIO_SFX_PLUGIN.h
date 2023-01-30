// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <memory>
#include <GameFramework/PlayerController.h>
#include <Camera/CameraActor.h>
#include "Tones.h"
#include "AUDIO_SFX_PLUGINCommands.h"

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
    void GeneratePerlinNoise();
    bool OnGeneratePerlinNoise();
    void FillToolBar();
    void AddMenuBarExtension(FMenuBarBuilder&);
    void FillMenu(FMenuBuilder&);
    
private:
    void RegisterMenus();
    TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

};