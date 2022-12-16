// Copyright Epic Games, Inc. All Rights Reserved.

#include "AUDIO_SFX_PLUGINStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FAUDIO_SFX_PLUGINStyle::StyleInstance = nullptr;

void FAUDIO_SFX_PLUGINStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FAUDIO_SFX_PLUGINStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FAUDIO_SFX_PLUGINStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("AUDIO_SFX_PLUGINStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FAUDIO_SFX_PLUGINStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("AUDIO_SFX_PLUGINStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("AUDIO_SFX_PLUGIN")->GetBaseDir() / TEXT("Resources"));

	Style->Set("AUDIO_SFX_PLUGIN.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FAUDIO_SFX_PLUGINStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FAUDIO_SFX_PLUGINStyle::Get()
{
	return *StyleInstance;
}
