from string import Template

lib = [
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

classDECLARATION = Template('''
#pragma once

namespace ToneLibrary
{

	template<typename T, typename U>
	class sfx_$U
	{
	public:
		sfx_$U();
	};
    
}''')

classDEFIINITION = Template('''
#include "sfx_$U.h"

using namespace ToneLibrary;

template<typename T, typename U>
sfx_$U<T, U>::sfx_$U()
{
	
}
''')

FileH = Template('sfx_$U.h')
FileCPP = Template('sfx_$U.cpp')
IncludeFileH = Template('#include "sfx_$U.h"\n')

with open("includes.generated.h",'w') as h:
    for fn in lib:
        with open(FileH.safe_substitute(U=fn),'w') as f:
            f.write(classDECLARATION.safe_substitute(U=fn))
        with open(FileCPP.safe_substitute(U=fn),'w') as g:
            g.write(classDEFIINITION.safe_substitute(U=fn))
        h.writelines(IncludeFileH.safe_substitute(U=fn))

print("Q.E.D.")