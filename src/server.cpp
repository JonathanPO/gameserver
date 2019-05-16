#include <memory>

#include "definitions.h"
#include "Server.h"
#include "Connection.h"

void writeSync(net::socket& sock, std::string message);
void writeAsync(net::socket& sock, std::string message);
void writeCallback(const net::error_code& ec, size_t bytes_transferred);

int main() {
	unsigned short port = 3333;
	auto ip = net::ip_address_v4::any();

	net::endpoint ep(ip, port);
	net::io_service ios;
	net::io_service::work work(ios);

	net::Server server(ios, ep);

	server->onMessage([](net::CommunicationChannel& channel, std::string request){
		if(request == "pontos"){
			channel.write("20");
		} else if(request == "numeroSecreto"){
			channel.write("42");
		} else{
			channel.write("Requisição Inválida");
		}

	});

	server.start();
	ios.run();

	return 0;
}
