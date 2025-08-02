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

	PlaceOrderMessage pom;
	pom.SetSymbol("AWSA");
	pom.userID = 38950493040;
	pom.quantity = 50;
	pom.isBuy = 0;
	pom.limit = 1200.0f;
	pom.orderType =	PlaceOrderMessage::Type::Limit;
	
	PlaceOrderMessage pom2;
	
	char* dataBuffer2 = new char[pom.GetSerializedSize()];

	pom.Serialize(dataBuffer2);
	pom.Print();

	pom2.Deserialize(dataBuffer2);
	pom2.Print();
	
	delete dataBuffer2;
	
	printf("Size of Place Order Message: %zu\n", pom.GetSerializedSize());



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