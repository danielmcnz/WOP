#include "CommandInterpreter.h"

void CommandInterpreter::InterpretCommand(std::string command,
	std::vector<ClientInfo>* clients,
	int connected_clients)
{
	command = command.substr(1, command.size());

	if (command == "clients")
	{
		ListClients(clients);
	}
	else if (command == "connected")
	{
		GetActiveClients(connected_clients);
	}
}

void CommandInterpreter::GetActiveClients(int connected_clients)
{
	std::cout << "There are currently " << connected_clients <<
		" connected" << std::endl;
}

void CommandInterpreter::ListClients(std::vector<ClientInfo> *clients)
{
	std::cout << "---------------" << std::endl;
	std::cout << "Connected clients: " << std::endl;
	for (ClientInfo client : *clients)
	{
		std::cout << client.id << std::endl;
	}
	std::cout << "---------------" << std::endl;
}
