from string import Template
import re

Lib = {}

nlpH = '''#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{
    template<typename T, typename U>
    class nlp_lib
    {
    public:
        nlp_lib();
        std::unordered_map<std::string, U> nlp_has;

    };
}
'''

nlpCPP = Template('''
#include "nlp.generated.h"

using namespace ToneLibrary;

template<typename T, typename U>
nlp_lib<T, U>::nlp_lib()
{
	
}

template<typename T, typename U>
nlp_lib<T, U>::nlp_has = {
$U
};
''')

with open("nlp.generated.h", 'w') as g:
    g.write(nlpH)
with open("corpus.generated.log",'r') as f:
    for fStr in f.readlines():
        has_result = re.search("^([^\n])+",fStr)
        is_valid = re.search("^[^#]",fStr)
        if has_result and is_valid:
            Lib[has_result[0]] = True
result = []
for fStr in Lib.keys():
    result += [fStr]
num = 0
buff = []
result.sort()
for fStr in result:
    buff += [Template("\t{ \"$U\", 0x").safe_substitute(U=fStr) + '{:05x}'.format(num) + ' }']
    num += 1
with open("nlp.generated.cpp", 'w') as h:
    h.write(nlpCPP.safe_substitute(U=",\n".join(buff)))
print("Q.E.D.")