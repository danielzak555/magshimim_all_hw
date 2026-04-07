#include "ShiftText.h"
#include "SubstitutionText.h"
#include "CaesarText.h"
#include "FileHelper.h"
#include "BonusText.h"
#include <iostream>

// encryption class related
#define SHIFTING_KEY 10
#define SUB_DICTIONARY_FILE_NAME "dictionary.csv"
#define ENCRYPTED_FILE_NAME "encrypted.txt"

// ************
// menu related
// ************

// string maximal size

#define MAX_STRING_SIZE 1024

// user choices
#define ENCRYPT_STRING '1'
#define DECRYPT_STRING '2'
#define ENCRYPT_FILE '3'
#define DECRYPT_FILE '4'
#define PRINT_NUM_OF_TEXTS '5'
#define EXIT_PROGRAM '6'

// algorithm choices
#define CAESAR '1'
#define SHIFT '2'
#define SUB '3'

// output options
#define SHOW_ON_SCREEN "1"
#define SAVE_TO_FILE "2"


using std::cout;
using std::endl;


/*local functions*/
void menu();
void showWelcomeBanner();
void showMenuOptions();
void showStringOptions(const bool encrypt);
void showFileOptions(const bool encryptOrDecrypt);
std::string showMessageMenu(const std::string text, bool encrypt);
bool checkInput(const std::string s);

/*
This is the main function of the program.
It starts the Menu
*/
int main()
{
	
	menu();


	return 0;
}

/*
Displays the welcome screen and pauses the program
*/
void showWelcomeBanner()
{
	cout << "	     .--------.        \n"
		<< "	    / .------. \\      \n"
		<< "	   / /        \\ \\	\n"
		<< "	   | |        | |		\n"
		<< "	  _| |________| |_		\n"
		<< "	.' |_|        |_| '.	\n"
		<< "	'._____ ____ _____.'	\n"
		<< "	| .'____'. |			\n"
		<< "	'.__.'.'    '.'.__.'	\n"
		<< "	'.__|Magshimim |__.'	\n"
		<< "	| '.'.____.'.' |		\n"
		<< "	'.___'.____.'____.'	\n"
		<< "	'.________________.'	\n\n";


	cout <<
		" _    _  ___  __    __  __  __  __  ___   \n"
		"( \\/\\/ )(  _)(  )  / _)/  \\(  \\/  )(  _)  \n"
		" \\    /  ) _) )(__( (_( () ))    (  ) _)  \n"
		"  \\/\\/  (___)(____)\\__)\\__/(_/\\/\\_)(___)  \n\n";

	system("pause");
	
}

/*
Displays the menu options
*/
void showMenuOptions()
{
	cout << "Please choose one of the following options:\n"
		<< "[1] -------- Encrypt a string\n"
		<< "[2] -------- Decrypt a string\n"
		<< "[3] -------- Encrypt a file\n"
		<< "[4] -------- Decrypt a file\n"
		<< "[5] -------- Show number of texts\n"
		<< "[6] -------- Exit\n";
}

/*
Manages string input and output
*/
void showStringOptions(const bool encryptOrDecrypt)
{


	cout << "Please enter a string (lowercase letters or panctuation symbols ',' '.')  \n";
	
	// reading string from std::cin, including whitespaces (ws)
	std::string inputString;
	std::getline(std::cin >> std::ws, inputString);

	if (!checkInput(inputString))
	{
		cout << "bad string format  \n";
		return;
	}
	std::string result = showMessageMenu(inputString, encryptOrDecrypt);

	std::cout << "Original text\n" << inputString << "\n\n";
	std::cout << "Changed text\n" << result << "\n\n";
	system("pause");

}


/*
encrypts or decrypts the string according to the user's choice.
*/
std::string showMessageMenu(const std::string text, bool encrypt)
{
	system("cls");

	char choice;
	cout << "Please choose which algorithm to use:  \n"
		<< "[1] ----- Caesar\n"
		<< "[2] ----- Shift\n"
		<< "[3] ----- Substitution \n";
	std::cin >> choice;

	std::string resultText;
	switch (choice)
	{
	case CAESAR:
		resultText = encrypt ? CaesarText::encrypt(text) : CaesarText::decrypt(text);
		break;

	case SHIFT:
		std::cout << "please choose the shift amount: ";
		int key;
		std::cin >> key;
		if (key > 26 || key < 1)
		{ 
			resultText = text;
		}
		else
		{
			resultText = encrypt ? ShiftText::encrypt(text, key) : ShiftText::decrypt(text, key);
		}
		break;

	case SUB:
		resultText = encrypt ? SubstitutionText::encrypt(text, SUB_DICTIONARY_FILE_NAME) : SubstitutionText::decrypt(text, SUB_DICTIONARY_FILE_NAME) ;
		break;
	}


	return resultText;


}

/*
Checks if a string is valid (lowcase letters and panctuation symbols ' ' ',' '.'
*/
bool checkInput(const std::string s)
{
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (!std::islower(s[i]) && s[i] != ' ' && s[i] != ',' && s[i] != '.')
		{
			return false;
		}
	}
	return true;
}

// Manages file input and output
void showFileOptions(const bool encryptOrDecrypt)
{
	std::string inputFileName;
	cout << "Please enter a file name to read \n";
	std::cin >> inputFileName;

	std::string text = FileHelper::readFileToString(inputFileName);
	std::string result = showMessageMenu(text, encryptOrDecrypt);


	std::string choice;
	cout << "Please choose one of the following options:\n"
		<< "[1] -------- Show encrypted file on screen\n"
		<< "[2] -------- Save encrypted file\n";
	std::cin >> choice;
	if (choice == SHOW_ON_SCREEN)
	{
		std::cout << "Decrypted text\n" << result << "\n\n";
	}
	else if (choice == SAVE_TO_FILE)
	{
		FileHelper::saveTextInFile(result, "encryptedFile.txt");
	}
	system("pause");
}

void menu()
{
	system("cls");
	showWelcomeBanner();
	showMenuOptions();
	char input;
	std::cin >> input;

	while (input != EXIT_PROGRAM)
	{
		if (input < '1' || input > '6')
		{
			system("cls");
			cout << "Wrong input! please choose a valid option, here are the options\n\n";
			showMenuOptions();
		}
		else if (input == ENCRYPT_STRING || input == DECRYPT_STRING)
		{
			const bool encryptOrDecrypt = (input == ENCRYPT_STRING);
			showStringOptions(encryptOrDecrypt);
		}
		else if (input == ENCRYPT_FILE || input == DECRYPT_FILE)
		{
			const bool encryptOrDecrypt = (input == ENCRYPT_FILE);
			showFileOptions(encryptOrDecrypt);
		}
		else if (input == PRINT_NUM_OF_TEXTS)
		{
			// using the public static variable in PlainText
			cout << "Number of texts created: " << PlainText::numOfTexts << "\n\n" ;
			system("pause");
		}
		system("clear");
		showMenuOptions();
		std::cin >> input;
	}

}

