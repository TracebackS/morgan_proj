/*
 * Implenmentation of fixscanner_sh.h
 */

#include "fixscanner_sh.h"

void fixScanning(const std::string & s, std::map<int, std::string> & fix_statement)
{
	FixTokenStream fts(s);
	while (!fts.empty())
	{
		int tag = fts.getIntToken();
		std::string val = fts.getStringToken();
		fix_statement[tag] = val;
	}
}

FixTokenStream::FixTokenStream(const std::string & s)
{
	sstream << s;
}

std::string FixTokenStream::getStringToken()
{
	std::string ans = "";
	char c;
	while (sstream.get(c))
	{
		switch (c)
		{
			case ';':
				return ans;
			default:
				ans += c;
		}
	}
	return ans;
}

int FixTokenStream::getIntToken()
{
	int ans = 0;
	sstream >> ans;
	char c;
	sstream.get(c);
	return ans;
}

void FixTokenStream::clear()
{
	std::string clear;
	std::getline(sstream, clear);
	sstream.clear();
}

bool FixTokenStream::empty()
{
	char c;
	if (sstream >> c)
	{
		sstream << c;
		return false;
	}
	sstream.clear();
	return true;
}
