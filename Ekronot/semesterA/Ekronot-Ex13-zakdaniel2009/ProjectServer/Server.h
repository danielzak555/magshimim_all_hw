#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <mutex>
#include <map>
#include <string>

class Server
{
public:
	Server();
	~Server();
	void serve(int port);

private:

	void acceptClient();
	void clientHandler(SOCKET clientSocket);

	SOCKET _serverSocket;

	std::mutex _clientsMutex;
	std::map<std::string, SOCKET> _clients; // username , socket
};

