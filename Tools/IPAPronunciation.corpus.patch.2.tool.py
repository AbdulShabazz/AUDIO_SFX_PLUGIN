import re
import time as time

result = []

with open("pronounciation.corpus.generated.1674275980.4888992.log","r") as f:
    for wd in f.readlines():
        if re.search("_",wd):
            result += [wd]

archive_set = sorted(list(result))

with open("pronounciation.corpus.generated." + str(time.time()) + ".log","w") as g:
    for wd in archive_set:
        g.writelines(wd)

print("Q.E.D.")