// Apriorit Poland Summer 2023 Internship Program
// Inter-Process Communication - Client
// Szymon Siąkała

#include "Client.h"

int main(int argc, char* argv[])
{
    try
    {
        Client client("127.0.0.1", 12345);
        client.run(argv[1]);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}