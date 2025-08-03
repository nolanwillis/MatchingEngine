#include "TestMessage.h"
#include "PlaceOrderMessage.h"

#include <iostream>
#include <string>

int main()
{
	std::string input;
	std::cout << "Matching Engine running... Type 'q' to quit.\n";

	char* dataBuffer = new char[sizeof(int)];

	TestMessage message1(7);
	message1.Serialize(dataBuffer);
	message1.Print();
	
	TestMessage message2(5);
	message2.Deserialize(dataBuffer);
	message2.Print();

	delete dataBuffer;

	while (true)
	{
		std::cout << "> ";
		std::getline(std::cin, input);
		if (input == "exit")
			break;
	}
	return 0;

	/* Notes:
		Stuff to do 
			1. Add network project
			2. Get input queue / output queue working with messages
			3. Setup order book and pages for each symbol
			4. Create interface for applying different matching algorithms (FIFO for now)
	*/ 

	return 0; 
}