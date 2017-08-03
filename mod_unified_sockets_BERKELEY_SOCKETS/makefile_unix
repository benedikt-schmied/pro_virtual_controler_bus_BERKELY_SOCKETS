#makefile
# Created on: Jul 30, 2017
#     Author: bensch
PROJECTNAME = mod_unified_sockets_BERKELEY_SOCKETS
ARCHIVESUFFIX = .a 
ARCHIVEPREFIX = lib
EXECUTABLESUFFIX = 
EXECUTABLEPREFIX =

all: $(ARCHIVEPREFIX)$(PROJECTNAME)$(ARCHIVESUFFIX)

clean:
	rm $(ARCHIVEPREFIX)$(PROJECTNAME)$(ARCHIVESUFFIX)
	rm unified_sockets_unix.o

$(ARCHIVEPREFIX)$(PROJECTNAME)$(ARCHIVESUFFIX): unified_sockets_unix.o
	ar -q -o $@ $^
	
%.o : %.c
	gcc  -g -O0 -c -o $@ -I. $^
	