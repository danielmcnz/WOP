#include "client.h"

Client::Client()
	:
	server_socket(0),
	result(0),
	msgSize(0)
{
	ZeroMemory(&server_addr, 0);

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
	std::thread get_data(&Client::RecieveData, this, server_socket);
	std::thread send_data(&Client::SendData, this);

	get_data.join();
	send_data.join();
}

int Client::CloseServerSocket()
{
	std::terminate();

	result = closesocket(server_socket);
	if (result == SOCKET_ERROR)
	{
		std::cout << "Failed to close server socket" << std::endl;
		return 1;
	}

	return 0;
}

void Client::SendData()
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

		msgSize = send(server_socket, msg.data(), msg.size(), 0);
		if (msgSize == SOCKET_ERROR)
		{
			std::cout << "Failed to send data to server" << std::endl;
		}
	} while (msg != "exit");

	if (CloseServerSocket() != 0)
	{
		std::cout << "Failed to close server socket" << std::endl;
	}
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

	if (CloseServerSocket() != 0)
	{
		std::cout << "Failed to close server socket" << std::endl;
	}
}