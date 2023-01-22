import re
import json
from string import Template

syllables = {
    "a":True,
    "e":True,
    "i":True,
    "o":True,
    "u":True,
    "y":True,
    #"oo":True,
    #"ee":True,
    #"ou":True,
}

result = []

def getNextWord(word):
    #vowels = list("aeiouy")
    word = re.sub("[\n\s]+","",word)
    if len(word) < 2 or not re.findall("_", word):
        word = "" # preserve newlines
    return word

def splitIntoSyllables(word):
    wordFragmentArray = word.split("_")
    return wordFragmentArray

def addToCatalog(wordFragmentArray):
    for wordFragment in wordFragmentArray:
        if wordFragment not in syllables:
            syllables[wordFragment] = True

with open("pronounciation.corpus.generated.1674299232.2774985.log","r") as f:
    for word in f.readlines():
        addToCatalog( splitIntoSyllables( getNextWord( word )))

with open("syllable.corpus.generated.log","w") as f:
    syllables.pop("")
    fileBody = Template("$BODY")
    f.writelines( fileBody.safe_substitute( BODY=json.dumps( syllables, sort_keys=True, indent=2 )))

print("Q.E.D.")