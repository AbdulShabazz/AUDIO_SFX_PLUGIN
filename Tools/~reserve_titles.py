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

#

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

#

syllables = {
    "a":True,
    "e":True,
    "i":True,
    "ian":True,
    "ion":True,
}

with open("pronunciation.corpus.generated.2.log","r") as f:
    for wd in f.readlines():
        wd = re.sub("[\n]+", "", wd)
        for syllab in wd.split("_"):
            if len(syllab) > 2:
                syllables[syllab] = True

wordArray = []

for wd in words:
    result = ""
    buff = ""
    for letter in list(wd):
        buff += letter
        if buff in syllables:
            result += buff
            buff = ""
            if len(result) + 1 < len(wd):
                result += "_"
    result += buff
    if not re.findall("[_]+",result):
        syllables[wd] = True
    wordArray += [result]

print( json.dumps( wordArray, indent=2))

#

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

with open("pronounciation.corpus.generated.1674270011.0918517.log","r") as f:
    for wd in f.readlines():
        if re.search("_",wd):
            archive_[wd] = True # preserve newlines
        else:
            archive[wd] = True # preserve newlines

archive_ii = {}

for wd in dict.keys(archive_):
    tmp = re.sub("_", "", wd)
    if tmp and tmp[0] not in archive:        
       archive_ii[tmp] = True

archive = {}

for wd in dict.keys(archive_ii):
    archive_[wd] = True

result = []

for wd in dict.keys(archive_):
    result += [wd]

archive_set = sorted(list(result))

with open("pronounciation.corpus.generated." + str(time.time()) + ".log","w") as g:
    for wd in archive_set:
        g.writelines(wd)

archive_set = sorted(set(archive))

import json
from string import Template

myprompt = Template('''The following words are separated into syllables: $WORDS. Replace each word with its sound equivalent from the following table: ''')
myprompt = '''(1) Seperate each word by a newline, and (2) split each word into syllables, separated by underscores: '''
myprompt = '''
Given the custom IPA Dictionary:
`
    #ordinal = Sounds like
    "1st" = "f_u_r_s_t",
    "2nd" = "s_e_k_o_n_d",
    "3rd" = "th_i_r_d",
    #"th" = "",
    #Number = Sounds like
    "0" = "z_e2_r_o2",
    "1" = "w_o_n",
    "2" = "t_o3",
    "3" = "th_r_e2",
    "4" = "f_or",
    "5" = "f_i2_v",
    "6" = "s_i_k_s",
    "7" = "_s_e_v_e_n",
    "8" = "a2_t",
    "9" = "n_i2_n",
    #Letter = Sounds like
    "a2" = "A",
    "b2" = "B",
    "c2" = "C",
    "d2" = "D",
    "e2" = "E",
    "f2" = "F",
    "g2" = "G",
    "h2" = "H",
    "i2" = "I",
    "j2" = "J",
    "k2" = "K",
    "l2" = "L",
    "m2" = "M",
    "n2" = "N",
    "o2" = "O",
    "p2" = "P",
    "q2" = "Q",
    "r2" = "R",
    "s2" = "S",
    "t2" = "T",
    "u2" = "U",
    "v2" = "V",
    "w2" = "W",
    "x2" = "X",
    "y2" = "Y",
    "z2" = "Z",
    #Consonant = Sounds like
    "b", # as in "bat"
    "d", # as in "dog"
    "f", # as in "fish"
    "g", # as in "go"
    "h", # as in "hat"
    "j", # as in "jump, budget"
    "k", # as in "cat"
    "l", # as in "lip"
    "m", # as in "mat"
    "n", # as in "nap"
    "ng", # as in "sing"
    "p", # as in "pat"
    "r", # as in "rip"
    "s", # as in "sip"
    "sh", # as in "sheep"
    "t", # as in "tap"
    "ch", # as in "church, witch"
    "th", # as in "think, math, nothing"
    "th2", # as in "this, breathe"
    "v", # as in "vat"
    "w", # as in "wet"
    "hw", # as in "where, somewhat"
    "y", # as in "yacht, yes, onion"
    "z", # as in "zoo, zip, easy"
    "z2", # as in "measure, television, beige"
    #"Vowel":
    "a", # as in "apple, hat, bat"
    "a2", # as in "aid, bait, day"
    "a3", # as in "arm, father, aha"
    "a4", # as in "air, careful, wear"
    "a5", # as in "bought"
    "e", # as in "bet, ever, head"
    "e2", # as in "beet, eat, seed, need"
    "i", # as in "it, finishes"
    "i2", # as in "I, ice, deny"
    "o", # as in "odd, waffle"
    "o2", # as in "letter 'o', owe, road"
    "o3", # as in "good, book"
    "o4", # as in "out, how, loud"
    "u", # as in "up, mother"
    "u2", # as in rude, brute
    "ou", # as in "about, problem, circus"
`
What is the Custom IPA spellings for: '''

                    #th = threading.Thread(target=issueQuery, args=(wd,g,))
                    #th.start()
                    #worker += [th]
#for th in worker:
#    th.join()

#with open("pronounciation.corpus.generated.log","w") as g:
#    g.writelines(json.dumps(syllable, sort_keys=True, indent=2))

    #buff = []
    #for choice in response.choices: 
    #    buff += ["_".join(list(re.sub("[\n/]+", "", choice.text)))]
    #statement = "  " + word + " : " + json.dumps(buff) + ",\n"
    #statement = "  " + word + " : " + "_".join(list(re.sub("[\n/]+", "", response.choices[0].text)))
    #g.writelines(statement+"\n")
    #print(statement)

from string import Template
MAXTHREADS = 18
# import IPADictionary # Ex 'IPADictionary.Consonant["ch"] # (True)', 'IPADictionary.Vowel["a"] # (True)'
import IPASpellToSpeech # Ex IPASpellToSpeech["u"] = "oo" >> "m_a_s_a_ch_oo_s_e_t_s"
vowel = {
    "a":True,
    "e":True,
    "i":True,
    "o":True,
    "u":True
}

pattern = r'([bcdfghjklmnpqrstvwxz]*[aeiouy]*[bcdfghjklmnpqrstvwxyz]*)'
syllable = {}

        #for phonemeGroup in re.findall(pattern, word):
        #    if phonemeGroup and not syllable.get(phonemeGroup):
        #        syllable[phonemeGroup] = True

#resume = False
resume = True

        #if resume and re.search('^'+resume,line):
        #    resume = True
        #if resume:

            if not re.search("^#", txt):
                txt = re.sub("_", "-", txt)
                word = re.sub("[\'\.\n]+", "", txt)
                #th = threading.Thread(target=IPATagger, args=word)
                #th.daemon = True
                #th.start()
                if len(buff) < MAXTHREADS:
                    buff += [threading.Thread(target=IPATagger, args=(word,))]
                    #buff += [word]
                else:
                    for th in buff:
                        th.start()
                    for th in buff:
                        th.join()
                    #thd = []
                    #for i in range(0,MAXTHREADS):
                    #    thd += [threading.Thread(target=IPATagger, args=buff[i])]
                    #for th in thd:
                    #    th.start()
                    #for th in thd:
                    #    th.join()
                    buff = []
#thd = []
#for i in range(0,MAXTHREADS):
#    thd += [threading.Thread(target=IPATagger)]
#for th in thd:
#    th.start()
#for th in thd:
#    th.join()

#with open("IPATagger.log","w+") as errlog:
#    errlog.writelines(word+'\n')