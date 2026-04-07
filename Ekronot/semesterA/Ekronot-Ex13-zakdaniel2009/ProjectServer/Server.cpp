#include "Server.h"
#include "Helper.h"
#include <exception>
#include <iostream>
#include <thread>
#include <fstream>
#include <algorithm>

Server::Server()
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Server::~Server()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void Server::serve(int port)
{

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		acceptClient();
	}
}


void Server::acceptClient()
{

	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET client_socket = accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;
	// the function that handle the conversation with the client
	std::thread t(&Server::clientHandler, this, client_socket);
	t.detach();
}


void Server::clientHandler(SOCKET clientSocket)
{
	try
	{
		while (true)
		{
			// here we will read from the socket and respond to the client
			// according to the protocol that we have defined
			int message_type = Helper::getMessageTypeCode(clientSocket);

			switch (message_type)
			{
			case MT_CLIENT_LOG_IN:
			{
				int name_len = Helper::getIntPartFromSocket(clientSocket, 2);
				std::string username = Helper::getStringPartFromSocket(clientSocket, name_len);

				{
					std::lock_guard<std::mutex> lock(_clientsMutex);
					_clients[username] = clientSocket;
				}

				std::string all_users;
				{
					std::lock_guard<std::mutex> lock(_clientsMutex);
					for (const auto& pair : _clients)
					{
						all_users += pair.first + "&";
					}
					if (!all_users.empty())
					{
						all_users.pop_back();
					}
				}

				Helper::send_update_message_to_client(clientSocket, "", "", all_users);

				break;
			}
			case MT_CLIENT_UPDATE:
			{
				int target_name_len = Helper::getIntPartFromSocket(clientSocket, 2);
				std::string target_username = Helper::getStringPartFromSocket(clientSocket, target_name_len);

				std::string myName;
				{
					std::lock_guard<std::mutex> lock(_clientsMutex);
					for (const auto& pair : _clients)
					{
						if (pair.second == clientSocket)
						{
							myName = pair.first;
							break;
						}
					}
				}

				std::string fileName;
				if (myName < target_username)
				{
					fileName = myName + "&" + target_username + ".txt";
				}
				else
				{
					fileName = target_username + "&" + myName + ".txt";
				}

				std::cout << "Processing conversation file: " << fileName << std::endl;

				std::ofstream file(fileName, std::ios::app);
				if (!file.is_open()) {
					throw std::exception("could not open file");
				}

				int messToSend_size = Helper::getIntPartFromSocket(clientSocket, 5);
				std::string messToSend;
				if(messToSend_size > 0) {
					messToSend = "&MAGSH_MESSAGE&&Author&" + myName + "&DATA&" + Helper::getStringPartFromSocket(clientSocket, messToSend_size);
					file << messToSend << std::endl;
				}
				file.flush();
				file.close();

				std::string file_content;
				std::ifstream readFile(fileName);

				if (!readFile.is_open()) {
					throw std::exception("could not open file for reading");
				}

				else {
					std::string line;
					while (std::getline(readFile, line)) {
						file_content += line + "\n";
					}
					if (!file_content.empty() && file_content.back() == '\n') {
						file_content.pop_back();
					}
				}
				readFile.close();

				std::string all_users;
				{
					std::lock_guard<std::mutex> lock(_clientsMutex);
					for (const auto& pair : _clients)
					{
						all_users += pair.first + "&";
					}
					if (!all_users.empty())
					{
						all_users.pop_back();
					}
				}

				Helper::send_update_message_to_client(clientSocket, file_content, target_username, all_users);

				break;
			}
			default:
			{
				throw std::exception("Unknown message type received from client");
			}
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Client disconnected: " << e.what() << std::endl;
		closesocket(clientSocket);

		{
			std::lock_guard<std::mutex> lock(_clientsMutex);
			for (auto it = _clients.begin(); it != _clients.end(); ++it)
			{
				if (it->second == clientSocket)
				{
					_clients.erase(it);
					break;
				}
			}
		}
	}
}