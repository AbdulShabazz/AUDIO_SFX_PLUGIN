import re
import time as time

archive = []

with open("pronounciation.corpus.generated.1674236673287006500.log","r") as f:
    with open("pronounciation.corpus.generated." + str(time.time()) + ".log","w") as g:
        for wd in f.readlines():
            archive += [wd] # preserve newlines
        archive_set = sorted(set(archive))
        for wd in archive_set:
            g.writelines(wd)

print("Q.E.D.")