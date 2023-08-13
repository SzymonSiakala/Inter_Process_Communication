#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <boost/asio.hpp>

class Server
{
private:
	boost::asio::io_context io_context;
	boost::asio::ip::tcp::acceptor acceptor;
	std::ofstream file;

	void receive_name(boost::asio::ip::tcp::socket& socket);;
	void recieve_file(boost::asio::ip::tcp::socket& socket);

public:
	Server(const int port);
	void run();
};