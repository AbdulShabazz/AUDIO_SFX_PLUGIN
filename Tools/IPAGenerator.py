# import IPADictionary # Ex 'IPADictionary.Consonant["ch"] # (True)', 'IPADictionary.Vowel["a"] # (True)'
import re
import json
import threading
from string import Template
import IPASpellToSpeech # Ex IPASpellToSpeech["u"] = "oo" >> "m_a_s_a_ch_oo_s_e_t_s"

MAXTHREADS = 18

vowel = {
    "a":True,
    "e":True,
    "i":True,
    "o":True,
    "u":True
}

pattern = r'([bcdfghjklmnpqrstvwxz]*[aeiouy]*[bcdfghjklmnpqrstvwxyz]*)'
syllable = {}

def SyllableInspector(word):
    try:
        syllable[word] = "_".join(list(word))
        #for phonemeGroup in re.findall(pattern, word):
        #    if phonemeGroup and not syllable.get(phonemeGroup):
        #        syllable[phonemeGroup] = True
    except Exception as e:
        pass # print(e)

with open("database.corpus.generated.log","r") as f:
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
    with open("pronounciation.corpus.generated.log","w") as g:
        g.writelines(json.dumps(syllable, sort_keys=True, indent=2))

print("Q.E.D.")