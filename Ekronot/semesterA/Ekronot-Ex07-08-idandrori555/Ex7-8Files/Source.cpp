/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/
#define _CRT_SECURE_NO_WARNINGS
#include "Pipe.h"
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <chrono>
#include <cstring>
#include "Game.h"

using std::cout;
using std::endl;
using std::string;


int main()
{
	srand(time_t(NULL));

	
	Pipe p;
	bool isConnect = p.connect();
	
	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			isConnect = p.connect();
		}
		else 
		{
			p.close();
			return 0;
		}
	}
	

	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	Game game;                													// ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	game.initializeGame();                                                      // ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

	//std::string initialBoard = game.getBoardStateWithPlayer(0);           //   remove the // from this line and
	//strcpy(msgToGraphics, initialBoard.c_str());                          //   and this one
	//p.sendMessageToGraphics(msgToGraphics);   // send the board string    //   and this one too

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		
		std::string backMsg = "";
		backMsg = game.processMove(msgFromGraphics);
		strcpy(msgToGraphics, backMsg.c_str());

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);   

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
	return 0;
}