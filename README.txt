/brief:

 This small application shall provide a TCP server, which receives data
 from different nodes (e.g. virtual CAN nodes) and transmits those
 message to all other nodes that are connected to this network.

 We will employ TCP/IP technology in order to be independent from e.g. 
 CAN bus networks and additionally to be able to test on an abstract level.

 This is just a short and quick solution to build this
 litte test framework on windows as well as on linux.
 Can be replaced in future with BOOST library

/nomenclature:

pro_virtual_controller_bus_BERKELY_SOCKETS
 |             |                 | 
 |             |                 |-- BERKELY_SOCKETS  : dependency
 |             |-------------- virtual controller bus : project nanming
 |--------------------------------.-------------- pro : project identifier

/structure:
 |-- pro_virtual_controller_bus_BERKELY_SOCKETS
	"main project"
 |-- test_virtual_controller_bus_BERKLEY_SOCKETS
	"test code for this project"
 |-- test_virtual_controller_bus_clients
	"some test clients"
