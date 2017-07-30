#makefile
# Created on: Jul 30, 2017
#     Author: bensch

all: pro_virtual_controller_bus_BERKELY_SOCKETS

clean:
	rm pro_virtual_controller_bus_BERKELY_SOCKETS
	rm main.o unified_sockets_unix.o queue.o

pro_virtual_controller_bus_BERKELY_SOCKETS: main.o unified_sockets_unix.o queue.o
	gcc -o $@ $^ -lpthread
	
%.o : %.c
	gcc -c -o $@ -I. $^
	