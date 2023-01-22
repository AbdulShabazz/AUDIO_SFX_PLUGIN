import os
import re
import json
import time as time
import threading

class update_todos:

    archive = {}
    completed_archive = {}
    todo_archive = {}
    todos = []
    
    def _populate_todo_archive(self):
        RESUME_KEYWORD = ""
        resume_ready = True
        with open("database.corpus.generated.optimized.log","r") as f:
            for wd in f.readlines():
                if not resume_ready and re.search("^"+RESUME_KEYWORD, wd):
                    resume_ready = True
                if resume_ready and not re.search("^#", wd):
                    wd = re.sub("[\'\.]+", "", wd)
                    self.todo_archive[wd] = True

    def _populate_archive(self): # the latest archive
        with open("pronunciation.corpus.generated.1674299232.2774985.log","r") as g:
            for wd in g.readlines():
                wd = wd.lower()
                self.completed_archive[wd] = True
                word = re.sub("[_]+", "", wd)
                if word != wd and word in self.completed_archive: # remove unformatted dups
                    self.completed_archive.pop(word)
                self.archive[word] = True

    def update(self):

        th_0000 = threading.Thread(target=self._populate_todo_archive)
        th_0001 = threading.Thread(target=self._populate_archive)

        th_0000.start()
        th_0001.start()

        th_0000.join()
        th_0001.join()

        self.todos = []

        with open("pronunciation.corpus.todo.generated.log","w") as f:
            for word in dict.keys(self.todo_archive):
                if word not in self.archive:
                    self.todos += [word]
                    f.writelines(word) # preserve newlines

        print("Q.E.D.")