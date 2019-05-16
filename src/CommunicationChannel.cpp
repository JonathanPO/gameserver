#include <iostream>
#include <string>
#include <memory>
#include <functional>

#include "CommunicationChannel.h"

const std::string net::CommunicationChannel::MESSAGE_SEPARATOR = "\r\n\r\n";

net::CommunicationChannel::CommunicationChannel(net::socket_ptr socket){
	:socket_(socket)
}

net::CommunicationChannel::~CommunicationChannel(){

}

void net::CommunicationChannel::onRead(OnReadHandler handler);

void net::CommunicationChannel::onWrite(OnWriteHandler handler);

void net::CommunicationChannel::read(net::CommunicationChannel::OnReadHandler handler){
	net::streambuf_ptr buffer(new net::streambuf());
	boost::asio::async_read_until(
		*socket, 
		*buffer,
		MESSAGE_SEPARATOR, 
		std::bind(
			&net::CommunicationChannel::handleRead,
			this,
			std::placeholders::_1,
			buffer, 
			handler
		)
	);
}

void net::CommunicationChannel::write(std::string message, net::CommunicationChannel::OnWriteHandler handler){
	net::streambuf_ptr buffer(new net::streambuf());
	std::ostream output_stream(&(*buffer));
	output_stream << message << MESSAGE_SEPARATOR;

	boost::asio::async_write(
		*socket, 
		*buffer, 
		std::bind(
			&net::CommunicationChannel::handleWrite, 
			this, 
			std::placeholders::_1, 
			buffer, 
			handler
		)
	)
}

void net::CommunicationChannel::handleRead(net::error_code ec, net::streambuf_ptr buffer){
	if(ec){
		if(ec == boost::asio::error::wof){
			//aqui o socket foi desconectado
			//tratar apropriadamente
			return;
		}

		return;
	}

	std::istream input_stream(&(*buffer));
	std::stringstream string_stream;
	int line_number = 0;
	std::string line;

	while(input_stream){
		if(line_number > 0){
			string_stream << "\n";
		}

		std::getLine(input_stream, line);
		line_number++;
		string_stream << line;
	}

	std::string response = string_stream.str();
	auto position = response.find(MESSAGE_SEPARATOR);
	if(position != std::string::npos){
		response = response.substr(0, position);
	}

	if(onReadHandler_){
		onReadHandler_(response);
	}
}

void net::CommunicationChannel::handleWrite(net::error_code ec, net::streambuf_ptr buffer){
	if(ec){
		return;
	}

	if(onWriteHandler_){
		onWriteHandler_();
	}
}