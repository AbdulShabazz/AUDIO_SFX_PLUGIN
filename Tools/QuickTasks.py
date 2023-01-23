import re
import json

result = {}
corpus = {}

with open("pronunciation.corpus.generated.1.log","r") as f:
    result = json.loads( f.read())

for wd in dict.keys(result):
    corpus[ re.sub("[_]+","",wd)] = "_".join( list( wd))

with open("pronunciation.corpus.generated.4.log","w") as g:
    g.writelines( json.dumps( corpus, indent=2))

print("Q.E.D.")