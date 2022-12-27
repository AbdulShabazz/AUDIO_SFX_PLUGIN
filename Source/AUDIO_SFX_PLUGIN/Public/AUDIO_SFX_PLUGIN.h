// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

class IModuleInterface;
class FToolBarBuilder;
class FMenuBuilder;
class FViewportClient;

#include <memory>
#include <GameFramework/PlayerController.h>
#include <Camera/CameraActor.h>
#include <Engine/Classes/GameFramework/Character.h>

class FAUDIO_SFX_PLUGINModule : public IModuleInterface
{
public:

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    void CreatCameraViewportPlayerControllerEtc();
    
    /** This function will be bound to Command (by default it will bring up plugin window) */
    void PluginButtonClicked();

private:
    TObjectPtr<UWorld> World;
    TObjectPtr<ACameraActor> Camera;
    TObjectPtr<APlayerController> PlayerController;
    //TObjectPtr<UGameViewportClient> ViewportClient;
    TObjectPtr<FViewportClient> ViewportClient;
    TObjectPtr<FViewport> Viewport;
    
private:

    void RegisterMenus();

    TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
    TSharedPtr<class FUICommandList> PluginCommands;
};
