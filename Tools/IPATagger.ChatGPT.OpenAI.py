import os
import re
import time as time
import openai
import threading

syllable ={}

openai.api_key = os.getenv("OPENAI_API_KEY")

def issueQuery(word):        
    time.sleep(1001)
    response = openai.Completion.create(model="text-davinci-003", prompt="What is the IPA spelling for " + word + "?")
    syllable[word] = "_".join(list(re.sub("[\n]+", "", response.choices[0].text)))

worker = []
with open("database.corpus.generated.optimized.log","r") as f:
    for wd in f.readlines():
        word = re.sub("[\'\.\n]+", "", wd)
        try:
            th = threading.Thread(target=issueQuery, args=(wd,))
            th.start()
            worker += [th]
        except Exception as e:
            print(e)

for th in worker:
    th.join()

with open("pronounciation.corpus.generated.log","w") as g:
    g.writelines(json.dumps(syllable, sort_keys=True, indent=2))