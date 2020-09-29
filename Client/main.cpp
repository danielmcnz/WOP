#include "client.h"

int main(int argc, char** argv)
{
	Client client;

	char* ip = argv[1];

	client.StartClient(ip);

	return 0;
}