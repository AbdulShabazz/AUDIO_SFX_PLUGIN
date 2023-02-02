from string import Template
import re
import threading

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

MyPyClassDeclarationH = Template('''sfx_$SFXClass.h''')
MyPyClassDefinitionCPP = Template('''sfx_$SFXClass.cpp''')

MyPyClassDeclaration = Template('''
#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{

	template<typename T, typename U>
    class sfx_$SFXClass
    {
    public:
        sfx_$SFXClass();
    };

}''')

MyPyClassDefinition = Template('''
#include "sfx_$SFXClass.h"

using namespace ToneLibrary;

template<typename T, typename U>
sfx_$SFXClass<T, U>::sfx_$SFXClass()
{
	
}''')

def AddModule(T,U,fn):    
    with open(U.safe_substitute(SFXClass=fn),'w') as f:
        f.writelines(T.safe_substitute(SFXClass=fn))

worker = []

for fn in sfx_LIBRARY:
    th0 = threading.Thread(target=AddModule, args=(MyPyClassDeclaration, MyPyClassDeclarationH, fn,))
    th1 = threading.Thread(target=AddModule, args=(MyPyClassDefinition, MyPyClassDefinitionCPP, fn,))
    th0.start()
    th1.start()
    worker += [th0]
    worker += [th1]

for th in worker:
    th.join()

print("Q.E.D.")