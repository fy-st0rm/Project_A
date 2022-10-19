#pragma once
#include "../global.h"
#include "opcode.h"

class Client
{
public:
	Client(const std::string& ip, int port);
	~Client();

public:
	int run();
	void send_payload(int opcode, Json::Value& payload);
	Json::Value recv_payload();

private:
	std::string ip;
	int port;

	int client_fd;
	struct sockaddr_in address;
};
