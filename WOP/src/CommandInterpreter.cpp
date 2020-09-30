#include "CommandInterpreter.h"

CommandInterpreter::CommandInterpreter()
{
	// I just wanna be deleted
}

//CommandInterpreter::CommandInterpreter(std::vector<int> *clients,
//	std::vector<sockaddr_in> *client_addrs, int *connected_clients)
//{
//	this->connected_clients = *connected_clients;
//
//	for (int i = 0; i < clients->size(); ++i)
//	{
//		this->clients[i] = (*clients)[i];
//	}
//
//	for (int i = 0; i < client_addrs->size(); ++i)
//	{
//		this->client_addrs[i] = (*client_addrs)[i];
//	}
//}

//CommandInterpreter::~CommandInterpreter()
//{
//	clients.clear();
//	client_addrs.clear();
//}

void CommandInterpreter::InterpretCommand(std::string command,
	std::vector<int> clients, std::vector<sockaddr_in> client_addrs,
	int connected_clients)
{
	if (command == ".clients")
	{
		GetActiveClients(connected_clients);
	}
}

void CommandInterpreter::GetActiveClients(int connected_clients)
{
	std::cout << "There are currently " << connected_clients <<
		" connected" << std::endl;
}
