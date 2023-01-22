import re

from string import Template

lib = [
    "index.noun",
    "index.verb",
    "index.adv",
    "index.adj",
    "index.sense"
]

req = [
'^([\S])+',
'^([\S])+',
'^([\S])+',
'^([\S])+',
'^([^%])+'
]

idx = 0

FileDIR = Template("wn3.1/$U")

with open('corpus.generated.log','w') as ff:
    for fn in lib:
        with open(FileDIR.safe_substitute(U=fn),'r') as f:        
            ff.writelines( Template("\n#$U\n").safe_substitute(U=fn) )
            for fStr in f.readlines():
                try:
                    ff.writelines( re.search(req[idx],fStr)[0] +"\n" )
                except Exception as e:
                    print(e) 
        idx += 1
print("Q.E.D.")