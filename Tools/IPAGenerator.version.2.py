
import re
import json
import threading
from string import Template

syllable = {}

def SyllableInspector(word):
    try:
        syllable[word] = "_".join(list(word))
    except Exception as e:
        pass # print(e)

with open("database.corpus.generated.optimized.log","r") as f:
    with open("pronounciation.corpus.generated.log","w") as g:
        worker = []
        for line in f.readlines():
            if not re.search("^#", line):
                line = re.sub("[\'\.\n]+", "", line)
                word = re.sub("\-+", "_", line)
                for wd in word.split("_"):
                    th = threading.Thread(target=SyllableInspector, args=(wd,))
                    th.start()
                    worker += [th]
        for th in worker:
            th.join()
        g.writelines(json.dumps(syllable, sort_keys=True, indent=2))

print("Q.E.D.")