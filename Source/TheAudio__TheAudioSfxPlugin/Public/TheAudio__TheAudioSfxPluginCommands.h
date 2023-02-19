// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TheAudio__TheAudioSfxPluginStyle.h"

class FTheAudio__TheAudioSfxPluginCommands : public TCommands<FTheAudio__TheAudioSfxPluginCommands>
{
public:

	FTheAudio__TheAudioSfxPluginCommands()
		: TCommands<FTheAudio__TheAudioSfxPluginCommands>(TEXT("TheAudio__TheAudioSfxPlugin"), NSLOCTEXT("Contexts", "TheAudio__TheAudioSfxPlugin", "TheAudio__TheAudioSfxPlugin Plugin"), NAME_None, FTheAudio__TheAudioSfxPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};