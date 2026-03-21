#include "../include/dev.hpp"
#include "../include/tcp.hpp"
#include "../include/snmp.hpp"
#include "../utils/utilsfoo.hpp"

#include <iomanip>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <string>

std::string tcp_state_to_string(unsigned int state) {
    switch (state) {
        case 1: return 	"ESTABLISHED";
        case 2: return 	"SYN_SENT";
	case 3: return 	"SYN_RECV";
        case 4: return 	"FIN_WAIT1";
        case 5: return 	"FIN_WAIT2";
        case 6: return 	"TIME_WAIT";
        case 7: return 	"CLOSE";
        case 8: return 	"CLOSE_WAIT";
        case 9: return 	"LAST_ACK";
        case 10: return "LISTEN";
        case 11: return "CLOSING";
        default: return "UNKNOWN";
    }
}

void p_tcp(const std::vector<TcpEntry>& entries) {

	std::cout << std::left
        	 << std::setw(5)  << "SL"
        	 << std::setw(25) << "Local Address"
        	 << std::setw(25) << "Remote Address"
        	 << std::setw(15) << "State"
        	 << std::setw(15) << "Queue(Tx/Rx)"
        	 << std::setw(10) << "Drops"
        	 << "\n";

    	for(const auto& e: entries) {
		std::cout << std::setw(5)  << e.sl
        	     << std::setw(25) << htostr(e.local_address)
        	     << std::setw(25) << htostr(e.remote_address)
        	     << std::setw(15) << tcp_state_to_string(e.state)
        	     << std::setw(15) << (std::to_string(e.tx_queue) 
				     + "/" + std::to_string(e.rx_queue))
        	     << std::setw(10) << e.drops
        	     << "\n";
   	 }
}

void p_ip_stats(const std::vector<IpStats>& stats) {
    using std::cout;
    using std::setw;
    for (const auto& s : stats) {
        cout<< std::left;
        cout<< setw(35) << "Forwarding Enabled"
             << (int)s.is_forwarding_enabled << "\n";
        cout<< setw(35) << "Default TTL"
             << (int)s.default_ttl << "\n";
        cout<< setw(35) << "Total Packets Received"
             << s.total_packets_received << "\n";
        cout<< setw(35) << "Incoming Discarded Packets"
             << s.incoming_discarded_packets << "\n";
        cout<< setw(35) << "Delivered to Transport"
             << s.packets_delivered_to_transport << "\n";
        cout<< setw(35) << "Total Packets Sent"
             << s.total_packets_sent << "\n";
        cout<< setw(35) << "Outgoing Discarded Packets"
             << s.outgoing_discarded_packets << "\n";
        cout<< setw(35) << "Packets With No Route"
             << s.packets_with_no_route << "\n";
        cout<< setw(35) << "Total Packets Transmitted"
             << s.total_packets_transmitted << "\n";
    }
}

void p_dev(std::vector<struct InterfaceBandwidthStats>& interf){
	//std::string interfaceStat;
	using std::setw;
	std::cout << setw(10) 
			<< "Interface Name" << setw(20) 
			<< "Received Packets" << setw(25) 
			<< "Transmited Packets" << setw(25)
			<< "Received Packets Drop" << setw(20)
			<< "Transmited Packets Drop" << std::endl;
	for(const auto& Intfb: interf){
		std::cout << setw(10) 
			<< Intfb.iface << setw(5) 
			<< Intfb.received_packets        << setw(20) 
			<< Intfb.transmited_packets      << setw(25)
			<< Intfb.received_drop 		 << setw(20)
			<< Intfb.transmited_drop         << std::endl;
	}
}

int main(){
while(true){
	std::vector <struct InterfaceBandwidthStats> netdev = r_NetDev();
 	std::vector<struct TcpEntry> nettcp = r_NetTcp();
	std::vector<struct IpStats> netsnmp = r_snmp();
	if(netdev.size() == 0 || nettcp.size() == 0 || netsnmp.size() == 0){
		std::cout << "Error While reading /proc/net/ " << std::endl;
		//return -1;
	}
	
	p_dev(netdev);
	std::cout << "----------------------\n";
	p_tcp(nettcp);
	std::cout << "----------------------\n";
	p_ip_stats(netsnmp);
	std::cout << "----------------------\n";
	



	sleep(30);
	std::cout << "\033[2J\033[H";
	}
	return 0;
}
