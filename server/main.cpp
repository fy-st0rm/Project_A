#include "server.h"

int main()
{
	Server server("127.0.0.1", 5050);
	server.run();
	return 0;
}
