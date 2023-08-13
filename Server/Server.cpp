#include "Server.h"

Server::Server(const int port) : acceptor(io_context)
{
	boost::system::error_code error;
	acceptor.open(boost::asio::ip::tcp::v4(), error);

	if (error)
	{
		throw boost::system::system_error(error, "Unable to open the acceptor.");
	}

	acceptor.bind(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port), error);

	if (error)
	{
		throw boost::system::system_error(error, "Unable to bind the acceptor to the port.");
	}

	acceptor.listen(boost::asio::socket_base::max_listen_connections, error);

	if (error)
	{
		throw boost::system::system_error(error, "Unable to listen for connections.");
	}

	std::cout << "Server is running on port: " << port << std::endl;
}

void Server::receive_name(boost::asio::ip::tcp::socket& socket)
{
	std::string file_name = "";
	boost::system::error_code error;
	boost::asio::streambuf receive_buffer;
	boost::asio::read_until(socket, receive_buffer, '\n', error);

	if (error)
	{
		throw boost::system::system_error(error, "Unable to receive the file name.");
	}

	std::istream input_stream(&receive_buffer);
	std::getline(input_stream, file_name);

	if (input_stream.fail())
	{
		throw std::runtime_error("Unable to parse the file name.");
	}

	file.open(file_name, std::ios::binary);

	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open the file.");
	}

	std::cout << "Receiving file with name: " << file_name << std::endl;
}

void Server::recieve_file(boost::asio::ip::tcp::socket& socket)
{
	char data[1024] = { 0 };
	boost::system::error_code error;

	while (true)
	{
		const size_t length = socket.read_some(boost::asio::buffer(data), error);

		if (error == boost::asio::error::eof)
		{
			break;
		}
		else if (error)
		{
			throw boost::system::system_error(error, "Unable to receive the file.");
		}

		if (!file.is_open())
		{
			throw std::runtime_error("Unable to open the file.");
		}

		file.write(data, length);
	}

	if (file.is_open())
	{
		file.close();
	}

	std::cout << "File received and saved." << std::endl;
}

void Server::run()
{
	while (true)
	{
		boost::asio::ip::tcp::socket socket(io_context);
		acceptor.accept(socket);

		std::cout << "Client connected." << std::endl;

		receive_name(socket);

		recieve_file(socket);
	}
}