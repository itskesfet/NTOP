#pragma once

#include <cstdint>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>

std::vector<struct IpStats> r_snmp();

struct IpStats {
    uint8_t  is_forwarding_enabled;        // Router forwarding?
    uint8_t  default_ttl;                  // TTL

    uint64_t total_packets_received;   
    uint64_t header_error_packets;      
    uint64_t address_error_packets; 

    uint64_t unknown_protocol_packets;    
    uint64_t incoming_discarded_packets;  
    uint64_t packets_delivered_to_transport; 

    uint64_t total_packets_sent;          
    uint64_t outgoing_discarded_packets; 
    uint64_t packets_with_no_route; 

    uint64_t reassembly_failed_packets;   
    uint64_t total_packets_transmitted;   
};

