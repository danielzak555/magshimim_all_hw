 #include "Queue.h"
 #include <iostream>
 #include <sstream>
 #include <windows.h> // WinApi header - needed for setting console color

 using std::cout;
 using std::endl;

 #define GREEN 2
 #define DARK_RED 4
 #define PURPLE 5
 #define YELLOW 6
 #define LIGHT_BLUE 9
 #define LIGHT_GREEN 10
 #define TEAL 11
 #define RED 12
 #define LIGHT_YELLOW 14
 #define WHITE 15

 void set_console_color(unsigned int color)
 {
 	// colors are 0=black 1=blue 2=green and so on to 15=white
 	// colorattribute = foreground + background * 16
 	// to get red text on yellow use 4 + 14*16 = 228
 	// light red on yellow would be 12 + 14*16 = 236
 	// a Dev-C++ tested console application by vegaseat 07nov2004

 	HANDLE hConsole;

 	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 	SetConsoleTextAttribute(hConsole, color);
 }

 std::string removeElementsAndGetPrintedQueue(Queue* q)
 {
 	std::stringstream output;
 	while (!isEmpty(q))
 	{
 		output << dequeue(q) << " ";
 	}
 	// removing the last letter (space)
 	std::string outputString = output.str();
 	outputString = outputString.substr(0, outputString.length() - 1);
 	return outputString;
 }

 bool test1()
 {
 	bool result = false;

 	try
 	{
 		set_console_color(LIGHT_BLUE);
 		// check basic data structure functions
 		cout << 
 			"*******************************\n"  << 
 			"Test 1 - basic queue functions\n" << 
 			"*******************************\n" << endl;
 		set_console_color(WHITE);

 		cout << "Initializing queue with size 5 ... \n" << endl;
 		Queue* q0 = new Queue;
 		initQueue(q0, 5);

 		bool empty = isEmpty(q0);
 		cout << "Checking if queue is empty ... \n"
 			<< "Expected: true\n"
 			<< "Got     : " << (empty ? "true" : "false")
 			<< "\n" << endl;

 		if (!empty)
 			// queue is not empty - test failed
 			return false;

 		const std::string queue0elements = "1 4 9 16 25";

 		cout << "Adding elements to queue ... " << queue0elements << "\n" << endl;
 		for (int i = 0; i < 5; i++)
 		{
 			enqueue(q0, (i+1) * (i+1));
 		}

 		bool full = isFull(q0);
 		cout << "Checking if queue is full ... \n"
 			<< "Expected: true\n"
 			<< "Got     : " << (full ? "true" : "false")
 			<< "\n" << endl;

 		if (!full)
 			// queue is not empty - test failed
 			return false;

 		std::string output = removeElementsAndGetPrintedQueue(q0);
 		cout << "Removing elements and printing queue ...\n"
 			<< "Expected: " << queue0elements << "\n"
 			<< "Got     : " << output
 			<< "\n " << endl;
		
 		if (output != queue0elements)
 		{
 			return false;
 		}

 		cout << "Cleaning queue...\n" << endl;
 		cleanQueue(q0);
 		delete q0;
 	}
 	catch (...)
 	{
 		std::cerr << "Test crashed" << endl;
 		return false;
 	}

 	return true;

 }


 bool test2()
 {
 	bool result = false;

 	try
 	{
 		set_console_color(LIGHT_BLUE);
 		// check basic data structure functions
 		cout <<
 			"*******************************\n" <<
 			"Test 2 - two queues\n" <<
 			"*******************************\n" << endl;
 		set_console_color(WHITE);

 		cout << "Initializing first queue with size 3 ... \n" << endl;
 		Queue* q1 = new Queue;
 		initQueue(q1, 3);

 		const std::string queue1elements = "10 20 30";

 		cout << "Adding elements to first queue ... " << queue1elements << "\n" << endl;
 		for (int i = 0; i < 3; i++)
 		{
 			enqueue(q1, (i + 1) * 10);
 		}

 		cout << "Initializing second queue with size 5 ... \n" << endl;
 		Queue* q2 = new Queue;
 		initQueue(q2, 5);

 		bool empty = isEmpty(q2);
 		cout << "Checking if second queue is empty ... \n"
 			<< "Expected: true\n"
 			<< "Got     : " << (empty ? "true" : "false")
 			<< "\n" << endl;

 		if (!empty)
 			// queue is not empty - test failed
 			return false;

 		const std::string queue2elements = "1 2 3 4 5";

 		cout << "Adding elements to second queue ... " << queue2elements << "\n" << endl;
 		for (int i = 0; i < 5; i++)
 		{
 			enqueue(q2, i + 1 );
 		}

 		bool full = isFull(q2);
 		cout << "Checking if second queue is full ... \n"
 			<< "Expected: true\n"
 			<< "Got     : " << (full ? "true" : "false")
 			<< "\n" << endl;

 		if (!full)
 			// queue is not empty - test failed
 			return false;

 		int dequeueResult = dequeue(q1);
 		cout << "Using dequeue() on first queue and printing element... \n" << endl
 			<< "Expected: 10\n"
 			<< "Got     : " << dequeueResult
 			<< "\n" << endl;

 		if (dequeueResult != 10)
 		{
 			return false;
 		}

 		dequeue(q2);
 		dequeue(q2);
 		std::string q2output = removeElementsAndGetPrintedQueue(q2);
 		cout << "Using dequeue() twice on second queue and printing queue... \n" << endl
 			<< "Expected: 3 4 5\n"
 			<< "Got     : " << q2output
 			<< "\n" << endl;

 		if (q2output != "3 4 5")
 		{
 			return false;
 		}

 		empty = isEmpty(q1);
 		cout << "Checking if first queue is empty ... \n"
 			<< "Expected: false\n"
 			<< "Got     : " << (empty ? "true" : "false")
 			<< "\n" << endl;

 		if (empty)
 			// queue is not empty - test failed
 			return false;


 		cout << "Cleaning first queue...\n" << endl;
		cleanQueue(q1);
 		delete q1;

 		cout << "Cleaning second queue...\n" << endl;
		cleanQueue(q2);
 		delete q2;
 	}
 	catch (...)
 	{
 		std::cerr << "Test crashed" << endl;
 		return false;
 	}

 	return true;

 }



 int main()
 {

 	bool test1Result = test1();
 	bool test2Result = test2();
 	if (test1Result && test2Result )
 	{
 		set_console_color(GREEN);
 		std::cout << "\n########## Ex1 Part1 Tests Passed!!! ##########\n" << endl;
 		set_console_color(WHITE);
 	}
 	else
 	{
 		set_console_color(RED);
 		std::cout << "\n########## TEST Failed :( ##########\n";
 		set_console_color(WHITE);
 	}


 	return 0;
 }