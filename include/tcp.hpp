#pragma once 

#include <string>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

std::vector<struct TcpEntry> r_NetTcp();

struct TcpEntry {
    unsigned int sl;    
    std::string local_address;
    std::string remote_address;
    unsigned int state;  
    unsigned int tx_queue;
    unsigned int rx_queue;
    unsigned int timer_active;
    unsigned int retransmits;
    unsigned int uid;     
    unsigned int drops;           
};
