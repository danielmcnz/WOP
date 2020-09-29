#include "client.h"

Client::Client()
{
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("wsastartip falied\n");
	}
}

Client::~Client()
{
	WSACleanup();
}

int Client::StartClient(char* ip)
{
	if (Socket(ip) != 0)
	{
		return 1;
	}

	Connect();

	GetServerData();

	if (CloseServerSocket() != 0)
	{
		return 1;
	}
}

int Client::Socket(char* ip)
{
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket == INVALID_SOCKET)
	{
		std::cout << "Socket creation falied" << std::endl;
		return 1;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(DEFAULT_PORT);
	inet_pton(AF_INET, ip, &server_addr.sin_addr);

	return 0;
}

void Client::Connect()
{
	do
	{
		result = connect(server_socket, (sockaddr*)&server_addr,
			sizeof(server_addr));
	} while (result != 0);
	std::cout << "successfully connected to server" << std::endl;
}

void Client::GetServerData()
{
	//RecieveData(server_socket);
	std::thread get_data(&Client::RecieveData, this, server_socket);
	get_data.join();
}

int Client::CloseServerSocket()
{
	result = closesocket(server_socket);
	if (result == SOCKET_ERROR)
	{
		std::cout << "Failed to close server socket" << std::endl;
		return 1;
	}

	return 0;
}

void Client::RecieveData(int server_socket)
{
	std::vector<char> msgBuffer(256);
	while (msgSize = recv(server_socket, msgBuffer.data(),
		msgBuffer.size(), 0) > 0)
	{
		if (msgSize == SOCKET_ERROR)
		{
			std::cout << "Failed to receive data" << std::endl;
		}
		std::cout << "Server: ";
		for (int i = 0; i < msgBuffer.size(); ++i)
		{
			if (msgBuffer[i] == 0)
			{
				break;
			}
			std::cout << msgBuffer[i];
		}
		std::cout << std::endl;
		msgBuffer.clear();
		msgBuffer.resize(256);
	}
}