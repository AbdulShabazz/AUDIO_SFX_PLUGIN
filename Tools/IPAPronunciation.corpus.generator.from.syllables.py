import re
import json

corpus = {}

with open("pronunciation.corpus.generated.2.log","r") as f: # the latest pronunciation archive
    for syllableEntries in f.readlines():
        syllableEntries = re.sub("[\t\n\s]+","",syllableEntries)
        word = re.sub("[_]+","",syllableEntries)
        corpus[word] = syllableEntries

with open("pronunciation.corpus.generated.log","w") as f:
    f.writelines( json.dumps( corpus, sort_keys=True, indent=2 ))

print("Q.E.D.")