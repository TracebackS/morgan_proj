/* 
 * This file declare the 'Order' type
 */

#include<string>
#include<map>
#include<set>

#include "fixscanner_sh.h"

/*
 * Class: Order
 * ------------
 * Define the 'order', and ensure that it is valid.
 */

class Order {

public:

/*
 * Constructor: Order
 * Usage: Order order(s);
 * ----------------------
 * Initialize the 'Order' type.
 */

	Order(const std::string & s);

/*
 * Destructor: ~Order
 * Usage: default
 * --------------
 * Destruct the type.
 */

	~Order() {}

/*
 * Method: config
 * Usage: if (order.config(tag, val)) ...
 * --------------------------------------
 * Config the tag value of the order.
 */

	bool config(int tag, std::string val);

/*
 * Method: checkTag
 * Usage: std::string val = order.checkTag(tag);
 * ---------------------------------------------
 * Get the tag value. If it does not exist, return an empty string.
 */

	std::string checkTag(int tag);

/*
 * Method: toString
 * Usage: std::string order_message = order.toString();
 * ----------------------------------------------------
 * Print the order for human to read.
 */

	std::string toString();
	
/*
 * Method: isValid
 * Usage: if (order.isValid()) ...
 * -------------------------------
 * Judge whether the order is valid, if not, return false.
 */

	bool isValid();

/*
 * Method: matchOrder
 * Usage: char fill_statement = order.matchOrder(orderbook);
 * ---------------------------------------------------------
 * Match the order and return the statement (full fill, partial fill, or nothing has be done).
 */

	char matchOrder(std::set<Order> & orderbook);
/*
 * Method: cancelOrder
 * Usage: char cancel_statement = order.cancelOrder(orderbook);
 * ------------------------------------------------------------
 * Cancel the order.
 */

	char cancelOrder(std::set<Order> & orderbook);

/*
 * Private
 * -------
 */

private:
	std::map<int, std::string> order_statement;
	std::set<int> valid_tags;
};
