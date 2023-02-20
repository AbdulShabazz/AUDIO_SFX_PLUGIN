// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
//#include "Tones.h"

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

protected:
    // Forward class declarations
    class IEditor;
    class UEditor;
    class FTabTypeEntry;
    class IDocument;
    class FOnTabChanged;

    // Get all active docktab objects
    virtual TArray<SDockTab>& GetAllActiveTabs() = 0;

    // Gets TabIds of all children tabs of the active tab
    virtual void GetAllChildrenTabs(TArray<FTabId>& OutFTabIdsArrayRef, const TArray<SDockTab>& SDockTabActiveTabArrayConstRefT) = 0;

    // Gets the TabIds of all active tabs
    virtual void GetAllActiveTabIds(TArray<FTabId>& OutTabIdsArrayRef) = 0;

    // Activates a tab in the global tab manager
    virtual void ActivateTab(const TSharedRef<SDockTab> InTab) = 0;

    // Adds a new tab to the global tab manager
    virtual void AddTab(const TSharedRef<SDockTab> InTab) = 0;

    // Adds a new tab spawner to the global tab manager
    virtual void AddTabSpawner(const TSharedRef<FTabSpawnerEntry> InTabSpawnerEntry) = 0;

    // Removes a tab spawner from the global tab manager
    virtual void RemoveTabSpawner(const TSharedRef<FTabSpawnerEntry> InTabSpawnerEntry) = 0;

    // Finds a tab type by name
    virtual TSharedPtr<FTabTypeEntry> FindTabType(const FName TabTypeName) = 0;

    // Closes all tabs currently open in the global tab manager
    virtual void CloseAllTabs() = 0;

    // Closes all tabs associated with a specific editor
    virtual void CloseAllTabsForEditor(const TSharedRef<IEditor> InEditor) = 0;

    // Closes a document in the global tab manager
    virtual void CloseDocument(const TSharedRef<IDocument> InDocument) = 0;

    // Gets the number of tabs in the global tab manager
    virtual int32 GetNumTabs() = 0;

    // Gets the tab at a specified index
    virtual TSharedPtr<SDockTab> GetTabAtIndex(int32 InIndex) = 0;

    // Gets the index of a specified tab
    virtual int32 GetTabIndex(const TSharedRef<SDockTab> InTab) = 0;

    // Gets the tab type associated with a specified tab
    virtual TSharedPtr<FTabTypeEntry> GetTabType(const TSharedRef<SDockTab> InTab) = 0;

    // Gets all tabs in the global tab manager
    virtual TArray<TSharedRef<SDockTab>> GetAllTabs() = 0;

    // Called when a tab is closed in the global tab manager
    virtual void OnTabClosed(const TSharedRef<SDockTab> InClosedTab) = 0;

    // Opens a document in the global tab manager
    virtual void OpenDocument(const TSharedRef<IDocument> InDocument) = 0;

    // Registers a callback to be called when a tab is added or removed from the global tab manager
    virtual void RegisterTabChangeCallback(const FOnTabChanged InCallback) = 0;

    // Removes a tab from the global tab manager
    virtual void RemoveTab(const TSharedRef<SDockTab> InTab) = 0;

    // Sets the tab type for a specified tab
    virtual void SetTabType(const TSharedRef<SDockTab> InTab, const TSharedRef<FTabTypeEntry> InTabType) = 0;

    // Unregisters a previously registered tab change callback
    virtual void UnregisterTabChangeCallback(const FOnTabChanged InCallback) = 0;
};

class FToolBarBuilder;
class FMenuBuilder;

class FTheAudio__TheAudioSfxPluginModule : public IModuleInterface
{

public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:
    short TabCounterInt8 = 1;
    short TabIndexInt8 = 1;
	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
