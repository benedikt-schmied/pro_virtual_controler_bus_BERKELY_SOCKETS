#makefile
# Created on: Jul 30, 2017
#     Author: bensch

PROJECTNAME = test_mod_queue
ARCHIVESUFFIX = .a 
ARCHIVEPREFIX = lib
EXECUTABLESUFFIX = 
EXECUTABLEPREFIX =

all: $(EXECUTABLEPREFIX)$(PROJECTNAME)$(EXECUTABLESUFFIX)

clean:
	rm $(EXECUTABLEPREFIX)$(PROJECTNAME)$(EXECUTABLESUFFIX)
	rm main.o

$(EXECUTABLEPREFIX)$(PROJECTNAME)$(EXECUTABLESUFFIX): $(PROJECTNAME).o
	gcc  -g -O0 -o $@ $^ -lmod_queue -lpthread -L../mod_queue -lmod_queue -L../mod_queue
	
%.o : %.c
	gcc -c -g -O0 -o $@ -I. -I../mod_queue $^