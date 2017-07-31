#makefile
# Created on: Jul 30, 2017
#     Author: bensch

PROJECTNAME = test_virtual_controller_bus_clients
ARCHIVESUFFIX = .a 
ARCHIVEPREFIX = lib
EXECUTABLESUFFIX = 
EXECUTABLEPREFIX =

all: $(EXECUTABLEPREFIX)$(PROJECTNAME)$(EXECUTABLESUFFIX)

clean:
	rm $(EXECUTABLEPREFIX)$(PROJECTNAME)$(EXECUTABLESUFFIX)
	rm main.o

$(EXECUTABLEPREFIX)$(PROJECTNAME)$(EXECUTABLESUFFIX): main.o
	gcc -g -O0 -o $@ $^ -lpthread -lmod_unified_sockets_BERKELEY_SOCKETS -L../mod_unified_sockets_BERKELEY_SOCKETS
	
%.o : %.c
	gcc -g -O0 -c -o $@ -I. -I../mod_unified_sockets_BERKELEY_SOCKETS $^
	