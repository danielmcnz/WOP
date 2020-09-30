#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#include <string>
#include <iostream>
#include <vector>
#include <thread>

#include "CommandInterpreter.h"

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
	int StopServer();
	int CloseClientSocket(int client);

	int Login();

	void GetClients(int server_socket, std::vector<int>* clients,
		std::vector<sockaddr_in> *client_addrs);

	void SendToClients();
	void RecieveFromClients();

	void AssignPrivilege(int client);
private:
	sockaddr_in server_addr;
	int connected_clients, counted_clients;
	int server_socket;
	int result;
	int msgSize;
	//std::vector<ClientInfo> clients;
	std::vector<int> clients;
	std::vector<std::string> client_ids;
	std::vector<sockaddr_in> client_addrs;
private:
	//std::vector<std::thread> threads;
	std::thread get_clients;
	std::thread send_messages;
	std::thread recieve_messages;
private:
	CommandInterpreter cmd;
};