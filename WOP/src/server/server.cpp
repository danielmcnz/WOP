#include "server.h"

Server::Server()
	:
	server_socket(0),
	result(0)
{
	ZeroMemory(&server_addr, 0);

	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("wsastartip falied\n");
	}
}

Server::~Server()
{
	WSACleanup();
}

int Server::StartServer()
{
	if (Login() != 0)
	{
		return 1;
	}

	if (Socket() != 0)
	{
		return 1;
	}

	if (Bind() != 0)
	{
		return 1;
	}

	if (Listen() != 0)
	{
		return 1;
	}

	AcceptConnections();

	if (CloseClientSockets() != 0)
	{
		return 1;
	}
	
	return 0;
}

int Server::Socket()
{
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket == INVALID_SOCKET)
	{
		std::cout << "Failed to create socket" << std::endl;
		return 1;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(DEFAULT_PORT);
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY;

	return 0;
}

int Server::Bind()
{
	result = bind(server_socket, (sockaddr*)&server_addr,
		sizeof(server_addr));
	if (result == SOCKET_ERROR)
	{
		std::cout << "Failed to bind socket" << std::endl;
		return 1;
	}

	return 0;
}

int Server::Listen()
{
	result = listen(server_socket, BACKLOG);
	if (result == SOCKET_ERROR)
	{
		std::cout << "Listening failed" << std::endl;
		return 1;
	}

	return 0;
}

void Server::AcceptConnections()
{
	GetClients(server_socket, &clients, &client_addrs);
	SendToClients(&clients);

	/*std::thread get_clients(&GetClients, this, server_socket, 
		&clients, &client_addrs);
	std::thread send_messages(&SendToClients, this, &clients);

	get_clients.join();

	send_messages.join();*/
}

int Server::CloseClientSockets()
{
	for (int client : clients)
	{
		result = closesocket(client);
		if (result == SOCKET_ERROR)
		{
			std::cout << "Failed to close client socket" << std::endl;
			return 1;
		}
	}

	return 0;
}

int Server::Login()
{
	std::string username = "user";
	std::string password = "pass";

	std::string user_in;
	std::string pass_in;
	std::cout << "Username: ";
	std::cin >> user_in;
	std::cout << "Password: ";
	std::cin >> pass_in;
	if (strcmp(username.c_str(), user_in.c_str()) == 0)
	{
		if (strcmp(password.c_str(), pass_in.c_str()) == 0)
		{
			std::cout << "Successful Login" << std::endl;
			return 0;
		}
	}

	std::cout << "Incorrect credentials" << std::endl;

	return 1;
}

void Server::GetClients(int server_socket, std::vector<int>* clients,
	std::vector<sockaddr_in*>* client_addrs)
{
	do
	{
		int poo = 100;
		sockaddr_in* client_addr;
		int client_addrstrlen = sizeof(client_addr);
		int client;

		client = accept(server_socket, (sockaddr*)&client_addr,
			&client_addrstrlen);

		clients->push_back(client);
		client_addrs->push_back(client_addr);
	} while (true);
}

void Server::SendToClients(std::vector<int>* clients)
{
	std::string msg;
	do
	{
		msg.clear();
		std::cin >> msg;
		if (msg.size() > 255)
		{
			std::cout << "Message must be less than 256 bytes"
				<< std::endl;
			continue;
		}

		for (int client : *clients)
		{
			int size;
			size = send(client, msg.data(), msg.size(), 0);
			if (size == SOCKET_ERROR)
			{
				std::cout << "Failed to send message to client"
					<< std::endl;
			}
		}
	} while (msg != "exit");
}