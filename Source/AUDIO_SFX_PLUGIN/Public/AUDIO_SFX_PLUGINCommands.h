// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "Framework/Commands/UICommandList.h"
#include "AUDIO_SFX_PLUGINStyle.h"

class FAUDIO_SFX_PLUGINCommands : public TCommands<FAUDIO_SFX_PLUGINCommands>
{
public:

    FAUDIO_SFX_PLUGINCommands()
        : TCommands<FAUDIO_SFX_PLUGINCommands>(
            TEXT("AUDIO_SFX_PLUGIN"),
            NSLOCTEXT("Contexts", "AUDIO_SFX_PLUGIN", "AUDIO_SFX_PLUGIN Plugin"),
            NAME_None,
            FAUDIO_SFX_PLUGINStyle::GetStyleSetName())
    {
    };

    /** TCommands<> interface */
    virtual void RegisterCommands() override;

public:
    TSharedPtr<FUICommandInfo> OpenPluginWindow;
};