import re
import json
from string import Template

syllables = {}

with open("syllable.corpus.generated.log","r") as f:
    syllables = json.loads(f.read())

result = []

with open("pronounciation.corpus.todo.generated.log","r") as f:
    for word in f.readlines():
        word = re.sub("[\n]+","",word)
        wordEntry = ""
        buff = ""
        for letter in list(word):
            buff += letter
            if len(buff) > 1 and buff in syllables:
                wordEntry += buff
                buff = ""
                if len(wordEntry) + 1 < len(word):
                    wordEntry += "_"
        wordEntry += buff
        result.append(wordEntry)

with open("pronounciation.corpus.patch_addin.generated.log","w") as f:
    f.writelines( "\n".join( result))

print("Q.E.D.")