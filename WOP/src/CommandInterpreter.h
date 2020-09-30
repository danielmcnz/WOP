#pragma once

#include <WinSock2.h>

#include <iostream>
#include <vector>

class CommandInterpreter
{
public:
	CommandInterpreter();
	/*CommandInterpreter(std::vector<int> *clients,
		std::vector<sockaddr_in> *client_addrs, int *connected_clients);
	~CommandInterpreter();*/
	void InterpretCommand(std::string command, std::vector<int> clients,
		std::vector<sockaddr_in> client_addrs, int connected_clients);
private:
	void GetActiveClients(int connected_clients);
private:
	/*int connected_clients;
	std::vector<int> clients;
	std::vector<sockaddr_in> client_addrs;*/
};

