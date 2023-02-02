from string import Template
import re

sfx_LIBRARY = [
"BLANK",
"STATIC",
"CARTOON",
"CAMERA",
"MOVIE",
"WEATHER",
"TRAILER",
"EXPLOSION",
"DESTRUCTION",
"VEHICLE",
"SIREN",
"GUN",
"ROAD",
"TRAFFIC",
"CROWD",
"OFFICE",
"CONSTRUCTION",
"LAWNCARE",
"HOSPITAL",
"BANK",
"LAW",
"WAR",
"NATURE",
"FLUID",
"METALLIC",
"WOOD",
"PLASTICS",
"PAPER",
"FIRE",
"ORGANIC",
"BIOLOGICAL",
"SPACE",
"ORCHESTRAL",
"AIRPORT",
"CHARGING",
"SCI",
"ACOUSTIC",
"INDIE",
"SAVANNAH",
"TUNDRA",
"FOREST",
"SWAMP",
"MOUNTAINS",
"HILLS",
"WOODLANDS",
"TAIGA",
"POLAR",
"JUNGLE"
]

MyPyClassDeclarationH = Template('''sfx_$Class.h''')
MyPyClassDefinitionCPP = Template('''sfx_$Class.cpp''')

MyPyClassDeclaration = Template('''
#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{

	template<typename T, typename U>
    class sfx_$Class
    {
    public:
        sfx_$Class();
    };

}
''')

MyPyClassDefinition = Template('''
#include "$Class.h"

using namespace ToneLibrary;

template<typename T, typename U>
sfx_$Class<T, U>::sfx_$Class()
{
	
}
''')