#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#include <string>
#include <iostream>
#include <vector>
#include <thread>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT 4566
#define BACKLOG 10

class Server
{
public:
	Server();
	~Server();
	int StartServer();
private:
	int Socket();
	int Bind();
	int Listen();
	void AcceptConnections();
	int CloseClientSockets();

	int Login();

	void GetClients(int server_socket, std::vector<int>* clients,
		std::vector<sockaddr_in*>* client_addrs);

	void SendToClients(std::vector<int>* clients);
private:
	sockaddr_in server_addr;
	int server_socket;
	int result;
	std::vector<int> clients;
	std::vector<sockaddr_in*> client_addrs;
};