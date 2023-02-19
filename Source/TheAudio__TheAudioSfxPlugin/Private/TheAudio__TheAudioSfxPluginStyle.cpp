// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheAudio__TheAudioSfxPluginStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FTheAudio__TheAudioSfxPluginStyle::StyleInstance = nullptr;

void FTheAudio__TheAudioSfxPluginStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FTheAudio__TheAudioSfxPluginStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FTheAudio__TheAudioSfxPluginStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("TheAudio__TheAudioSfxPluginStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FTheAudio__TheAudioSfxPluginStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("TheAudio__TheAudioSfxPluginStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("TheAudio__TheAudioSfxPlugin")->GetBaseDir() / TEXT("Resources"));

	Style->Set("TheAudio__TheAudioSfxPlugin.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FTheAudio__TheAudioSfxPluginStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FTheAudio__TheAudioSfxPluginStyle::Get()
{
	return *StyleInstance;
}
