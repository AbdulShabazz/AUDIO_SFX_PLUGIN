from string import Template
import re
import http.client
import threading

MAXBYTES = 99999
MAXTHREADS = 18
STATUS_OK = 200

url_host = "www.collinsdictionary.com"
url = Template("/us/dictionary/english/$FN")

RESUME_KEYWORD = "3d"

archived = {}

def IPATagger(word):    
    try:           
        conn = http.client.HTTPSConnection(url_host)
        conn.request("GET",url.safe_substitute(FN=word))
        resp = conn.getresponse()
        if resp.status == STATUS_OK:
            with open(word, "w") as g:
                g.write(repr(resp.read(MAXBYTES)))
        else:
            print("STATUS 404 - PAGE NOT FOUND - " + word)
        conn.close()
    except Exception as e:
        print(e)

with open("TODO/AllEntries.log","r") as f:
    for txt in f.readlines():
        txt = re.sub("_", "-", txt)
        word = re.sub("[\'\.\n]+", "", txt)
        archived[word] = True

#resume = False
resume = True
with open("database.corpus.generated.log","r") as f:
    buff = []
    for txt in f.readlines():
        #if not resume and re.search('^'+RESUME_KEYWORD,txt):
        #    resume = True
        if resume:
            if not re.search("^#", txt):
                txt = re.sub("_", "-", txt)
                word = re.sub("[\'\.\n]+", "", txt)
                if not archived.get(word):
                    if len(buff) < MAXTHREADS:
                        buff += [threading.Thread(target=IPATagger, args=(word,))]
                    else:
                        for th in buff:
                            th.start()
                        for th in buff:
                            th.join()
                        buff = []
