/*
 * Implenmentation of order_sh.h
 */

#include "order_sh.h"
#include<sstream>

Order::Order(const std::string & s)
{
	fixScanning(s, order_statement);
	valid_tags.insert(35);
	valid_tags.insert(11);
	valid_tags.insert(41);
	valid_tags.insert(150);
	valid_tags.insert(39);
	valid_tags.insert(40);
	valid_tags.insert(44);
	valid_tags.insert(31);
	valid_tags.insert(32);
	valid_tags.insert(151);
	valid_tags.insert(6);
	valid_tags.insert(14);
	valid_tags.insert(54);
	valid_tags.insert(38);
	valid_tags.insert(55);
}

bool Order::config(int tag, std::string val)
{
	if (valid_tags.find(tag) == valid_tags.end())
		return false;
	else
	{
		order_statement[tag] = val;
		return true;
	}
}

std::string Order::checkTag(int tag) 
{
	if (order_statement.find(tag) == order_statement.end())
		return "";
	else
	{
		std::string ans = order_statement[tag];
		return ans;
	}
}

std::string Order::toString() 
{
	return order_statement[11] + " " + order_statement[0] + " " + order_statement[40] + " " + order_statement[32] + " " + order_statement[44] + " " + order_statement[39];
}

bool Order::isValid() 
{
	std::map<int, std::string>::iterator it = order_statement.begin();
	while (it != order_statement.end())
	{
		if (valid_tags.find(it->first) == valid_tags.end())
			return false;
		it ++;
	}
	return true;
}	

char Order::matchOrder(std::set<Order> & orderbook)
{
	std::set<Order>::iterator it = orderbook.begin();
	while (it != orderbook.end())
	{
		Order temp = *it;
		if (temp.checkTag(39) != "2")
		{
			std::stringstream ss;
			ss << order_statement[44];
			int self_price = 0;
			ss >> self_price;
			ss << temp.checkTag(44);
			int other_price = 0;
			ss >> other_price;
			ss << order_statement[32];
			int self_amount = 0;
			ss >> self_amount;
			ss << temp.checkTag(32);
			int other_amount = 0;
			ss >> other_amount;
			if ((order_statement[40] == "b" && temp.checkTag(40) == "s" && other_price < self_price && other_price > self_price * 0.95) || (order_statement[40] == "s" && temp.checkTag(40) == "b" && other_price > self_price && other_price * 0.95 < self_price))
			{
				if (self_amount > other_amount)
				{
					self_amount -= other_amount;
					ss << self_amount;
					std::string str_self_amount = "";
					ss >> str_self_amount;
					order_statement[32] = str_self_amount;
					order_statement[39] = "1";
					temp.config(32, "0");
					temp.config(39, "2");
					orderbook.erase(it);
					orderbook.insert(temp);
					return 'p';
				}
				else
				{
					other_amount -= self_amount;
					ss << other_amount;
					std::string str_other_amount = "";
					ss >> str_other_amount;
					order_statement[32] = "0";
					order_statement[39] = "2";
					temp.config(32, str_other_amount);
					temp.config(39, "1");
					orderbook.erase(it);
					orderbook.insert(temp);
					return 'f';
				}
			}
		}
		it ++;
	}
}

char cancelOrder(std::set<Order> & orderbook)
{
	if (orderbook.find(*this) == orderbook.end())
		return 'r';
	else if (order_statement[39] == "2")
	{
		orderbook.erase(orderbook.find(*this));
		return 'f';
	}
	else if (order_statement[39] == "1")
	{
		orderbook.erase(orderbook.find(*this));
		return 'p';
	}
	else
	{
		orderbook.erase(orderbook.find(*this));
		return 'c';
	}
}
