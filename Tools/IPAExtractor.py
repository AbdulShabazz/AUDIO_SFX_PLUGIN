#python
with open("TODO/AllEntries.log","r") as f:
    for txt in f.readlines():
        txt = re.sub("_", "-", txt)
        word = re.sub("[\'\.\n]+", "", txt)
        with open(word,"r") as g: