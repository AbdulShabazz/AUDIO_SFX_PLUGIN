import os
import re
import json
import time as time
import openai
import threading

archive = {}
completed_archive = {}
todo_archive = {}

def populate_todo_archive():
    RESUME_KEYWORD = ""
    resume_ready = True
    with open("database.corpus.generated.optimized.log","r") as f:
        for wd in f.readlines():
            if not resume_ready and re.search("^"+RESUME_KEYWORD, wd):
                resume_ready = True
            if resume_ready and not re.search("^#", wd):
                wd = re.sub("[\'\.]+", "", wd)
                todo_archive[wd] = True

def populate_archive(): # the latest archive
    with open("pronounciation.corpus.generated.1674299232.2774985.log","r") as g:
        for wd in g.readlines():
            wd = wd.lower()
            completed_archive[wd] = True
            word = re.sub("[_]+", "", wd)
            if word != wd and word in completed_archive: # remove unformatted dups
                completed_archive.pop(word)
            archive[word] = True

th_0000 = threading.Thread(target=populate_todo_archive)
th_0001 = threading.Thread(target=populate_archive)

th_0000.start()
th_0001.start()

th_0000.join()
th_0001.join()

todos = []

with open("pronounciation.corpus.todo.generated.log","w") as f:
    for word in dict.keys(todo_archive):
        if word not in archive:
            todos += [word]
            f.writelines(word) # preserve newlines

print("Q.E.D.")