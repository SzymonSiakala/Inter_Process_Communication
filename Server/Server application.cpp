// Apriorit Poland Summer 2023 Internship Program
// Inter-Process Communication - Server
// Szymon Siąkała

#include "Server.h"

int main()
{
	try 
	{
		Server server(12345);
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;
	}

	return 0;
}