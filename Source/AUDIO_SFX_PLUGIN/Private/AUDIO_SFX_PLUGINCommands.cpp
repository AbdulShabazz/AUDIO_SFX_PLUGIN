// Copyright Epic Games, Inc. All Rights Reserved.

#include "AUDIO_SFX_PLUGINCommands.h"

#define LOCTEXT_NAMESPACE "FAUDIO_SFX_PLUGINModule"

void FAUDIO_SFX_PLUGINCommands::RegisterCommands()
{
    UI_COMMAND(OpenPluginWindow, "The Audio SFX plugin", "Bring up the Audio SFX plugin window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
