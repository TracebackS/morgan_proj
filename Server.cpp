/*
 * Server Main File
 */

#include<array>
#include<set>
#include<iostream>
#include<boost/array.hpp>
#include<boost/asio.hpp>
#include<fstream>

#include "order_sh.h"

using boost::asio::ip::tcp;

void initOrderBook(std::set<Order> & orderbook, std::ifstream & ifs);

void updateOrderBook(std::set<Order> & orderbook, std::ofstream & ofs);

std::string dealOrder(const std::string & s, std::set<Order> & orderbook);

int main(int argc, char* argv[])
{
/* Initialize the boost part */
	boost::asio::io_service io_service;
	tcp::resolver resolver(io_service);
	/* ID should be configured */
	tcp::resolver::query query("192.168.1.233", "9876");
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	tcp::socket socket(io_service);
	boost::system::error_code error;
	std::ifstream ifs;
	ifs.open("orderbook.txt");
	std::set<Order> orderbook;
	initOrderBook(orderbook, ifs);
	ifs.close();
/* Main loop */
	while (true)
	{
		try
		{
			std::array<char, 256> input_buffer;
			std::size_t rsize = socket.read_some(boost::asio::buffer(input_buffer), error);
			std::string s(input_buffer.data(), input_buffer.data() + rsize);
			std::string result = dealOrder(s, orderbook);
			boost::asio::write(socket, boost::asio::buffer(result), error);
			std::set<Order>::iterator it = orderbook.begin();
			while (it != orderbook.end())
			{
				char fill_statement = it->matchOrder(orderbook);
				switch (fill_statement)
				{
					case 'p':
					{
						std::string update = "35=8;150=1;39=1";
						boost::asio::write(socket, boost::asio::buffer(update), error);
					}
					case 'f':
					{
						std::string update = "35=8;150=2;39=2";
						boost::asio::write(socket, boost::asio::buffer(update), error);
					}
				}
				it ++;
			}
			std::ofstream ofs;
			ofs.open("orderbook.txt");
			updateOrderBook(orderbook, ofs);
			ofs.close();
		}
		catch (const char* s)
		{
			std::cerr << s << std::endl;
		}
	}
}

std::string dealOrder(const std::string & s, std::set<Order> & orderbook)
{
	std::map<int, std::string> fix_statement;
	fixScanning(s, fix_statement);
	if (fix_statement[35] == "D")
	{
		Order this_order(s);
		orderbook.insert(this_order);
		return "35=8;150=0;39=0";
		/* fill_statement == 'n' means 'no match', 'p' means 'partial fill', 'f' means 'full fill' */
		char fill_statement = this_order.matchOrder(orderbook);
		switch (fill_statement)
		{
			case 'p':
				return "35=8;150=1;39=1";
			case 'f':
				return "35=8;150=2;39=2";
		}
	}
	else if (fix_statement[35] == "F")
	{
		if (this_order.cancelOrder(orderbook))
			return "35=8;150=4;39=4";
		return "35=9;39=8";
	}
	return ""; /* REJECT */
}

void initOrderBook(std::set<Order> & orderbook, std::ifstream & ifs)
{
	std::string str = "";
	while (std::getline(ifs, str))
	{
		Order order(str);
		orderbook.insert(order);
	}
}

void updateOrderBook(std::set<Order> & orderbook, std::ofstream & ofs)
{
	std::set<Order>::iterator it = orderbook.begin();
	while (it != orderbook.end())
	{
		ofs << it->toString() << std::endl;
		it ++;
	}
}
