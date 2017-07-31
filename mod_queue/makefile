#makefile
# Created on: Jul 30, 2017
#     Author: bensch
PROJECTNAME = mod_queue
ARCHIVESUFFIX = .a 
ARCHIVEPREFIX = lib
EXECUTABLESUFFIX = 
EXECUTABLEPREFIX =

all: $(ARCHIVEPREFIX)$(PROJECTNAME)$(ARCHIVESUFFIX)

clean:
	rm $(ARCHIVEPREFIX)$(PROJECTNAME)$(ARCHIVESUFFIX)
	rm queue.o

$(ARCHIVEPREFIX)$(PROJECTNAME)$(ARCHIVESUFFIX): queue.o
	ar -q -o $@ $^
	
%.o : %.c
	gcc  -g -O0 -c -o $@ -I. $^
	