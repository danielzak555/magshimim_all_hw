#include "WSAInitializer.h"
#include "Server.h"
#include "Helper.h"
#include <exception>
#include <iostream>
#include <string>
#include <thread>

int main()
{
    try
    {
        WSAInitializer wsaInit; // Initialize Winsock
        Server server;
        server.serve(8826); // Start server on port 54000
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}