#pragma once
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>

class Client
{
private:
	boost::asio::io_context io_context;
	boost::asio::ip::tcp::socket socket;
	std::string file_name;

	void send_name();
	void send_file();

public:
	Client(const std::string IP, const int port);
	void run(const std::string file_name);

};