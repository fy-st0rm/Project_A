#include "server.h"

Server::Server(const std::string& ip, int port)
	:ip(ip), port(port)
{
	if (create_sv() < 0)
	{
		std::cerr << "Failed to create server.\n";
		exit(1);
	}
	this->running = true;
	std::cout << "Sucessfully created server.\n";
}

Server::~Server()
{
}

int Server::create_sv()
{
	if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Socket failed: ");
		return -1;
	}
	
	// To reuse the address
	if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &this->opt, sizeof(this->opt)))
	{
		perror("Sockopt failed: ");
		return -1;
	}

	// Creating address
	this->address.sin_family = AF_INET;
	inet_pton(AF_INET, this->ip.c_str(), &this->address.sin_addr);
	this->address.sin_port = htons(this->port);
	this->addrlen = sizeof(this->address);
	
	// Binding
	if (bind(this->server_fd, (struct sockaddr*) &this->address, sizeof(this->address)) < 0)
	{
		perror("Binding failed: ");
		return -1;
	}
}

std::string Server::handle_opcode(int conn, Json::Value& data)
{
	Json::FastWriter writer;
	Json::Value reply_json;

	int opcode = std::atoi(writer.write(data["opcode"]).c_str());
	Json::Value payload = data["payload"];

	switch (opcode)
	{
		case OP_DISCONNECT:
		{
			reply_json["opcode"] = OP_OK;
			this->connections[conn].first = false;
			break;
		}
		default:
		{
			std::cout << "Opcode `" << opcode << "` hasnt been implemented." << std::endl;
			assert(false);
		}
	}

	std::string reply = writer.write(reply_json);
	return reply;
}

void Server::handle_conn(int conn)
{
	while (this->connections[conn].first)
	{
		char buffer[BUFF_SZ] = {0};
		if (read(conn, buffer, BUFF_SZ) > 0)
		{
			std::string msg(buffer);

			Json::Reader reader;
			Json::Value  data;
			reader.parse(msg, data, false);

			std::string reply = handle_opcode(conn, data);
			send(conn, reply.c_str(), reply.length(), 0);
		}
	}
	std::cout << "Disconnected: " << conn << std::endl;
}

void Server::run()
{
	std::cout << "Server listening on (" << this->ip << ":" << this->port << ")" << std::endl;
	listen(this->server_fd, 0);

	while (this->running)
	{
		// Accepting the connections
		int conn;
		if ((conn = accept(this->server_fd, (struct sockaddr*) &this->address, (socklen_t*) &this->addrlen)) < 0) 
			perror("Accept failed: ");

		// Making threads
		this->connections[conn] = std::make_pair(true, std::thread(&Server::handle_conn, this, conn));
	}
}
