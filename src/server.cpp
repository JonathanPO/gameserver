#include <iostream>
#include <string>

#include "definitions.h"
#include "Server.h"

void writeSync(net::socket& sock, std::string message);
void writeAsync(net::socket& sock, std::string message);
void writeCallback(const net::error_code& ec, size_t bytes_transferred);

int main() {
	unsigned short port = 3333;
	auto ip = net::ip_address_v4::any();

	net::endpoint ep(ip, port);
	net::io_service ios;

	net::Server server(ios, ep);

	server.onConnect([](net::Connection& conn)){
		std::cout << "Nova conexão" << std::endl;
	}

	server.start();
	ios.run();

	return 0;
}
