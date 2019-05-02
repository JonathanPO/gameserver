#include <iostream>

#include "definitions.h"

int main() {
	unsigned short port = 8080;
	std::string address = "127.0.0.1";

	auto ip = net::ip_address_v4::any();

	net::endpoint ep(ip, port);

	net::io_service ios;

	net::acceptor acceptor(ios);
	net::error_code error;

	acceptor.open(ep.protocol(), error);

	if(error.value() != 0){
		std::cout << "Erro ao criar socket! Código de erro:" << error.value() << ". Erro" 			<< error.message() << std::endl;
		return error.value();
	}

	acceptor.listen(30);

	net::socket sock(ios);

	acceptor.accept(sock);

	return 0;
}
