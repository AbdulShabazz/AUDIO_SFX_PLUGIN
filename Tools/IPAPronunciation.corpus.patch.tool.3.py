import re
import time as time

archive = {}
result = []

with open("pronounciation.corpus.generated.1674298280900144400.log","r") as f:
    for wd in f.readlines():
        tmp = re.sub("_","",wd)
        if tmp != wd and tmp in archive:
            archive.pop(tmp)
        archive[wd] = True
    for wd in archive:
        result += [wd.lower()]

archive_set = sorted(list(result))

with open("pronounciation.corpus.generated." + str(time.time()) + ".log","w") as g:
    for wd in archive_set:
        g.writelines(wd)

print("Q.E.D.")