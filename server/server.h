#pragma once
#include "global.h"

struct Connection
{
	int conn;
	std::string cmd;
	Json::Value payload;
};

class Server
{
public:
	Server(const std::string& ip, int port);
	~Server();

	void run();

private:
	int create_sv();

	std::string handle_opcode(int conn, Json::Value& data);
	void handle_conn(int conn);

	void cleaner();

private:
	std::string ip;
	int port;
	bool running;

	// Server database
	std::unordered_map<std::string, std::vector<Connection>> online_servers;

	// Connection threads
	std::unordered_map<int, std::pair<bool, std::thread>> connections;

	// Socket vars
	int server_fd;
	struct sockaddr_in address;
	int addrlen;
	int opt = 1;
};
