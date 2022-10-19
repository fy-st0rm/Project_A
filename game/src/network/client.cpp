#include "client.h"

Client::Client(const std::string& ip, int port)
	:ip(ip), port(port)
{
	// Creating the address
	this->address.sin_family = AF_INET;
	this->address.sin_port = htons(this->port);
	inet_pton(AF_INET, this->ip.c_str(), &this->address.sin_addr);
}

Client::~Client()
{
}

int Client::run()
{
	// Creating the socket
	if ((this->client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Socket failed: ");
		return -1;
	}

	// Trying to connect to the server
	if (connect(this->client_fd, (struct sockaddr*) &this->address, sizeof(this->address)) < 0)
	{
		perror("Failed to connect: ");
		return -1;
	}
	return 1;
}

void Client::send_payload(int opcode, Json::Value& payload)
{
	Json::Value data;
	data["opcode"] = opcode;
	data["payload"] = payload;

	Json::FastWriter writer;
	std::string msg = writer.write(data);

	send(this->client_fd, msg.c_str(), msg.length(), 0);
}

Json::Value Client::recv_payload()
{
	Json::Reader reader;
	Json::Value payload;

	char buffer[BUFF_SZ] = {0};
	if (read(this->client_fd, buffer, BUFF_SZ) > 0)
	{
		std::string msg(buffer);
		reader.parse(msg, payload, false);
	}
	return payload;
}

