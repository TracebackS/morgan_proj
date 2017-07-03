/*
 * Client Main File
 */

#include<array>
#include<set>
#include<iostream>
#include<boost/array.hpp>
#include<boost/asio.hpp>
#include<fstream>

using boost::asio::ip::tcp;

void help();

int main(int argc, char* argv[])
{
/* Initialize the boost part */
	boost::asio::io_service io_service;
	tcp::resolver resolver(io_service);
	/* ID should be configured */
	tcp::resolver::query query("192.168.1.233", "9876");
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	tcp::socket socket(io_service);
	std::cout << "Try to connect ..." << std::endl; // Connect to sth
	boost::asio::connect(socket, endpoint_iterator);
	std::cout << "Connected successfully!" << std::endl;
	boost::system::error_code error;
	while (true)
	{
		std::cout << "You want to? (Input 'h' for help)" << endl
			<< " >>> ";
		std::string cmd = "";
		std::getline(cin, cmd);
		if (cmd == "h")
			help();
		else
			std::string fix_statement = cmdScanning(cmd); //TODO
		std::array<char, 256> input_buffer;
		std::size_t rsize = socket.read_some(boost::asio::buffer(input_buffer), error);
		boost::asio::write(socket, boost::asio::buffer(result), error);
		std::string ack(input_buffer.data(), input_buffer.date() + rsize);
//		fixToClient(ack); //TODO
	}
}


void help()
{
	std::cout
		<< "To create a new order:" << endl
		<< "	buy(or sell) _price_ _amount_" << endl
		<< "	such as: buy 2000 20000" << endl
		<< "To cancel a order:" << endl
		<< "	cancel _orderid_" << endl
		<< "	such as: cancel xxxxxxxxxx" << endl;
}


