#pragma once

#include <string>
#include <winsock2.h>

struct ClientInfo
{
	int socket;
	int privilegeLvl;
	std::string id;
	sockaddr_in addr;
};