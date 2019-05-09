#ifndef CLIENT_H
#define CLIENT_H

#include <functional>

#include "definitions.h"

namespace net{
	class Client{
		public:
			using OnConnectedHandler = std::function<void()>;

			Client(net::io_service& io_service, net::endpoint ep);
			void connect();
			bool isConnected();
			void onConnected(net::Client::OnConnectedHandler handler);

		private:
			net::socket_ptr socket_;
			net::endpoint endpoint_;
			bool connected_;
			void handleConnect(net::error_code ec);
	};

};

#endif