#include <iostream>
#include <string>
#include "definitions.h"

int main() {
	unsigned short port = 3333;
	std::string address = "127.0.0.1";
	
	net::error_code error;

	auto ip = net::ip_address::from_string(address, error);
	
	if(error.value() != 0){
		std::cout << "IP inválido!" << std::endl;
		return error.value();
	}

	net::endpoint ep(ip, port);

	net::io_service ios;

	net::socket sock(ios);

	sock.open(ep.protocol(), error);

	if(error.value() != 0){
		std::cout << "Erro ao criar socket! Código de erro:" << error.value() << ". Erro" 			<< error.message() << std::endl;
		return error.value();
	}

	sock.connect(ep, error);

	if(error.value() != 0){
		std::cout << "Erro ao tentar conectar ao servidor! Código de erro:" << 
		error.value() << ". Erro" << error.message() << std::endl;
		return error.value();
	}

	std::cout << sock.local_endpoint().address().to_string() << std::endl;
	std::cout << sock.local_endpoint().port() << std::endl;
	std::cout << sock.remote_endpoint().address().to_string() << std::endl;
	std::cout << sock.remote_endpoint().port() << std::endl;

}
