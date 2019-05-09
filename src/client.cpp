#include <iostream>
#include <string>
#include <memory>
#include <functional>

#include "definitions.h"

void readSync(net::socket& sock, std::string& response);
void readAsync(net::socket& sock);
void readCallback(const net::error_code& ec, size_t bytes_transferred, net::streambuf_ptr sb);

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

	std::string response;
	readAsync(sock);
	std::cout << "Resposta do servidor: " << response << std::endl;

}

void readSync(net::socket& sock, std::string& response){
	net::streambuf buf;
	net::error_code ec;

	boost::asio::read(sock, buf, ec);

	std::istream input_stream(&buf);

	std::getline(input_stream, response);

}

void readAsync(net::socket& sock){
	net::streambuf_ptr buf(new net::streambuf());

	boost::asio::async_read(
		sock, 
		*buf, 
		std::bind(
			&readCallback, 
			std::placeholders::_1, 
			std::placeholders::_2, 
			buf
		)
	);
}

void readCallback(const net::error_code& ec, size_t bytes_transferred, net::streambuf_ptr sb){
	//std::istream input_stream(*sb);
	std::string response;
	//std::getline(input_stream, response);

	std::cout << "Resposta assíncrona: " << response << std::endl;
}

