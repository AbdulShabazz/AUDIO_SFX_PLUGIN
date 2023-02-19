// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheAudio__TheAudioSfxPluginCommands.h"

#define LOCTEXT_NAMESPACE "FTheAudio__TheAudioSfxPluginModule"

void FTheAudio__TheAudioSfxPluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "TheAudio__TheAudioSfxPlugin", "Bring up TheAudio__TheAudioSfxPlugin window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
