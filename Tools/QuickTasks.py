import re
import json

result = []

with open("pronunciation.corpus.generated.2.log","r") as f:
    for wd in f.readlines():
        wd = re.sub("\n", "", wd)
        result += [wd]

syllables = {}

for wd in sorted(result):
    syllables[re.sub("[_]+", "", wd)] = wd

with open("pronunciation.corpus.generated.3.log","w") as g:
    g.writelines( json.dumps( syllables, indent=2))

print("Q.E.D.")