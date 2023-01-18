from string import Template
import re
import http.client
import threading

MAXBYTES = 99999
MAXTHREADS = 18
STATUS_OK = 200
#url = Template("curl https://www.dictionary.com/browse/$FN --output '$FN.txt' --no-clobber --parallel --parallel-immediate --range 99999 --silent")
#url = Template("https://www.dictionary.com/browse/$FN")
url_host = "www.dictionary.com"
url = Template("/browse/$FN")

RESUME_KEYWORD = "dasyprocta_aguti"

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

resume = False
with open("database.corpus.generated.log","r") as f:
    buff = []
    for txt in f.readlines():
        if not resume and re.search('^'+RESUME_KEYWORD,txt):
            resume = True
        if resume:
            if not re.search("^#", txt):
                txt = re.sub("_", "-", txt)
                word = re.sub("[\'\.\n]+", "", txt)
                if len(buff) < MAXTHREADS:
                    buff += [threading.Thread(target=IPATagger, args=(word,))]
                else:
                    for th in buff:
                        th.start()
                    for th in buff:
                        th.join()
                    buff = []