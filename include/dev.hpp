#pragma once 

#include <string>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <iostream>

std::vector <struct InterfaceBandwidthStats> r_NetDev();

struct InterfaceBandwidthStats{
	std::string iface;
	unsigned long long 	received_bytes;
	unsigned long long 	transmitted_byte;
	unsigned long 		received_packets;
	unsigned long 		transmited_packets;
	unsigned long 		received_drop;
	unsigned long 		transmited_drop;
};

