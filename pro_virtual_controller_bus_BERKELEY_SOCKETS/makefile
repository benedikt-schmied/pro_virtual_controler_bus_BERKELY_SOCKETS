#makefile
# Created on: Jul 30, 2017
#     Author: bensch

all: pro_virtual_controller_bus_BERKELY_SOCKETS

pro_virtual_controller_bus_BERKELY_SOCKETS: main.o unified_sockets_unix.o
	gcc -o $@ $^ -lpthread
	
%.o : %.c
	gcc -c -o $@ -I. $^
	