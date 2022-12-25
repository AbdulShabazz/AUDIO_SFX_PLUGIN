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
    
    /** This function will be bound to Command (by default it will bring up plugin window) */
    void PluginButtonClicked();
    
private:

    void RegisterMenus();

    TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
    TSharedPtr<class FUICommandList> PluginCommands;
};

class FMYViewport : public FViewport
{
public:
    FMYViewport(TObjectPtr<FViewportClient> InViewportClient);
   ~FMYViewport();
    virtual void* GetWindow() override;
    virtual void MoveWindow(int32 NewPosX, int32 NewPosY, int32 NewSizeX, int32 NewSizeY) override;
    virtual void Destroy() override;
    virtual bool SetUserFocus(bool bFocus) override;
    virtual bool KeyState(FKey Key) const override;
    virtual int32 GetMouseX() const override;
    virtual int32 GetMouseY() const override;
    virtual void GetMousePos(FIntPoint& MousePosition, const bool bLocalPosition = true) override;
    virtual void SetMouse(int32 x, int32 y) override;
    virtual void ProcessInput(float DeltaTime) override;
    virtual FVector2D VirtualDesktopPixelToViewport(FIntPoint VirtualDesktopPointPx) const override;
    virtual FIntPoint ViewportToVirtualDesktopPixel(FVector2D ViewportCoordinate) const override;
    virtual void InvalidateDisplay() override;
    virtual TObjectPtr<FViewportFrame> GetViewportFrame() override;

};

class FMYViewportClient : public FViewportClient
{
public:
    FMYViewportClient() {};
   ~FMYViewportClient() {};
   TSharedPtr<FMYViewport> Viewport;

};

class FCamera : public ACameraActor
{
public:
    FCamera() {};
   ~FCamera() {};
};

class FCharacter : public ACharacter
{
public:
    FCharacter() {};
   ~FCharacter() {};

};

class FPlayerController : public APlayerController
{
public:
    FPlayerController() {};
   ~FPlayerController() {};
};
