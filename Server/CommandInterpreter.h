#pragma once

#include <WinSock2.h>

#include <iostream>
#include <vector>

#include "Structs.h"

class CommandInterpreter
{
public:
	void InterpretCommand(std::string command, std::vector<ClientInfo>* clients, int connected_clients);
private:
	void GetActiveClients(int connected_clients);
	void ListClients(std::vector<ClientInfo> *clients);
private:
	/*int connected_clients;
	std::vector<int> clients;
	std::vector<sockaddr_in> client_addrs;*/
};

