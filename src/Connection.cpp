#include "Connection.h"

net::Connection::Connection(net::io_service& io_service){
	: socket_(new net::socket(io_service))
}

net::socket& net::Connection::socket(){
	return *socket_;
}