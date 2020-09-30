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

class Client
{
public:
	Client();
	~Client();

	int StartClient(char* ip);
private:
	int Socket(char* ip);
	void Connect();
	void GetServerData();
	int CloseServerSocket();

	void SendData();
	void RecieveData(int server_socket);
private:
	sockaddr_in server_addr;
	int server_socket;
	int result;
	int msgSize;
};