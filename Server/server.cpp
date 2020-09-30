#include "server.h"

Server::Server()
	:
	connected_clients(0),
	counted_clients(0),
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
	get_clients = std::thread(&Server:: GetClients, this, server_socket,
		&clients, &client_addrs);
	send_messages = std::thread(&Server::SendToClients, this);
	recieve_messages = std::thread(&Server::RecieveFromClients, this, counted_clients);
	get_clients.join();
	send_messages.join();
	recieve_messages.join();

	while (true)
	{
		if (connected_clients > counted_clients)
		{
			++counted_clients;
		}
	}
}

int Server::StopServer()
{
	std::terminate();

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

int Server::CloseClientSocket(int client_num)
{
	result = closesocket(clients[client_num]);
	if (result == SOCKET_ERROR)
	{
		std::cout << "Failed to close client socket" << std::endl;
		return 1;
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
	std::vector<sockaddr_in>* client_addrs)
{
	
	while(true)
	{
		sockaddr_in client_addr = { 0 };
		socklen_t client_addrstrlen = sizeof(client_addr);
		int client;

		client = accept(server_socket, (sockaddr*)&client_addr,
			&client_addrstrlen);

		clients->push_back(client);
		client_addrs->push_back(client_addr);
		++connected_clients;

		char ip[INET_ADDRSTRLEN] = "";
		char port[100] = "";
		inet_ntop(AF_INET, &client_addr.sin_addr, ip, sizeof(ip));
		inet_ntop(AF_INET, &client_addr.sin_port, port, sizeof(port));
		std::cout << "Client connected from " << ip << ":" << port << std::endl;
	}
}

void Server::SendToClients()
{
	std::string msg;
	do
	{
		msg.clear();
		getline(std::cin, msg);
		if (msg.size() > 255)
		{
			std::cout << "Message must be less than 256 bytes"
				<< std::endl;
			continue;
		}

		for (int client : clients)
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

	if (StopServer() != 0)
	{
		std::cout << "Failed to close client sockets" << std::endl;
	}
}

void Server::RecieveFromClients(int id)
{
	std::vector<char> msgBuffer(256);
	do
	{
		if (connected_clients > 0)
		{
			msgBuffer.clear();
			msgBuffer.resize(256);
			char ip[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &client_addrs[id].sin_addr, ip, sizeof(ip));

			if (msgSize = recv(clients[id], msgBuffer.data(),
				msgBuffer.size(), 0) > 0)
			{
				std::cout << ip << ": ";
				for (char c : msgBuffer)
				{
					if (c != 0)
					{
						std::cout << c;
					}
				}
				std::cout << std::endl;
			}
			else
			{
				if (msgSize == SOCKET_ERROR)
				{
					std::cout << "Failed to recieve data" << std::endl;
					break;
				}
				else if (clients[id] > 0)
				{
					std::cout << "Client " << ip << " has disconnected" << std::endl;
					CloseClientSocket(0);
					--connected_clients;
					break;
				}
			}
		}
		else
		{
			continue;
		}
	} while (true);
}
