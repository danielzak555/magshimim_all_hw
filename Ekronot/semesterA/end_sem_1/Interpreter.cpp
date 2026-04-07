#include "Type.h"
#include "InterpreterException.h"
#include "SyntaxException.h"
#include "NameErrorException.h"
#include "Parser.h"
#include <iostream>

#define WELCOME "Welcome to Magshimim Python Interperter version 1.0 by "
#define YOUR_NAME "Daniel"


int main(int argc,char **argv)
{
	std::cout << WELCOME << YOUR_NAME << std::endl;

	std::string input_string;

	// get new command from user
	std::cout << ">>> ";
	std::getline(std::cin, input_string);
	
	while (input_string != "quit()")
	{
		try {
			Type* type = Parser::parseString(input_string);
			if (type != nullptr) {
				if (type->isPrintable()) {
					std::cout << type->toString() << std::endl;
				}
				if (type->isTemp()) {
					delete type;
				}
			}
		}
		catch (const SyntaxException& e) {
			std::cout << "Syntax Error: " << e.what() << std::endl;
		}
		catch (const NameErrorException& e) {
			std::cout << e.what() << std::endl;
		}


		// get new command from user
		std::cout << ">>> ";
		std::getline(std::cin, input_string);
	}

	Parser::clearVariables();

	return 0;
}
