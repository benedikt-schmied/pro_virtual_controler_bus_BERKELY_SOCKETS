#!/bin/bash
# this script will in a first step start the test server
# and later on start various test clients that will
# start to communicate with the test server
# of course we will fork those processes

./pro_virtual_controller_bus_BERKELEY_SOCKETS/pro_virtual_controller_bus_BERKELEY_SOCKETS &

./test_virtual_controller_bus_clients/test_virtual_controller_bus_clients 25 &
./test_virtual_controller_bus_clients/test_virtual_controller_bus_clients 26 &

