#include "Client.h"

Client::Client(const std::string IP, const int port) : socket(io_context), file_name("")
{
	boost::system::error_code error;
	try
	{
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(IP), port);
		socket.connect(endpoint, error);

		if (error)
		{
			throw boost::system::system_error(error, "Unable to connect to the server.");
		}
	}
	catch (const std::runtime_error& e)
	{
		throw std::runtime_error("Unable to create a client: " + std::string(e.what()));
	}

	std::cout << "Client connected to the server on IP: " << IP << " and port: " << port << std::endl;
}

void Client::send_name()
{
	boost::system::error_code error;
	boost::asio::write(socket, boost::asio::buffer(file_name + '\n'), error);

	if (error)
	{
		throw boost::system::system_error(error, "Unable to send the file name.");
	}

	std::cout << "Sending file with name: " << file_name << std::endl;
}

void Client::send_file()
{
	std::ifstream file(file_name, std::ios::binary);

	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open the file.");
	}

	char data[1024] = { 0 };;
	boost::system::error_code error;
	while (!file.eof())
	{
		file.read(data, sizeof(data));
		const size_t bytesRead = file.gcount();
		boost::asio::write(socket, boost::asio::buffer(data, bytesRead), error);
		if (error)
		{
			throw boost::system::system_error(error, "Unable to send the file.");
		}
	}

	if (file.is_open())
	{
		file.close();
	}

	std::cout << "File sent." << std::endl;
}

void Client::run(const std::string file_name)
{
	this->file_name = file_name;

	send_name();

	send_file();
}