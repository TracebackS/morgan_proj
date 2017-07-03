/*
 * This file declare a function to scan a fix string and store the message to a map.
 */

#include<iostream>
#include<string>
#include<map>
#include<sstream>

/*
 * Function: fixScanning
 * Usage: fixscanning(s, fix_statement);
 * -------------------------------------
 * Scanning the string 's' as fix tags and save them to map 'fix_statement'.
 */

void fixScanning(const std::string & s, std::map<int, std::string> & fix_statement);

/*
 * Class: FixTokenStream
 * ---------------------
 * This class can get tokens from a string of fix messages.
 */

class FixTokenStream {

public:

/*
 * Constructor: FixTokenStream
 * Usage: FixTokenStream fts(s);
 * -----------------------------
 * Initialize a FixTokenStream type with a string.
 */

	FixTokenStream(const std::string & s);

/*
 * Destructor: ~FixTokenStream
 * Usage: default
 * --------------
 * Destruct the type.
 */

	~FixTokenStream() {}

/*
 * Method: getStringToken()
 * Usage: std::string s = fts.getStringToken();
 * --------------------------------------------
 * Get a string token from the fix message. Must be the tag value.
 */

	std::string getStringToken();

/*
 * Method: getIntToken()
 * Usage: int n = fts.getIntToken();
 * ---------------------------------
 * Get a int token from the fix message. Must be the tag.
 */

	int getIntToken();

/*
 * Method: clear()
 * Usage: fts.clear();
 * -------------------
 * Clear the stream.
 */

	void clear();

/*
 * Method: empty()
 * Usage: if (fts.empty()) ...
 * ---------------------------
 * If the stream is empty, return true.
 */
	bool empty();

/*
 * Private
 * -------
 */

private:
	std::stringstream sstream;
};
