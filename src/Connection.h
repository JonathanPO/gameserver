#ifndef CONNECTION_H
#define CONNECTION_H

#include "definitions.h"

namespace net {
	class Connection{
		public:
			Connection(net::io_service& io_service);
			net::socket& socket();

		private:
			net::socket_ptr socket_;
		
	};

};

#endif