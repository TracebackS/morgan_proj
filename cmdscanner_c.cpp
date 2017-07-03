#include "cmdscanner_c.h"


std::string cmd Scanning(std::string cmd)
{
	std::string ans = "";
	std::stringstream ss;
	std::string temp_str = "";
	ss << cmd;
	ss >> temp_str;
	if (temp_str == "buy")
	{
		ans += "35=D;40=b;"
		ss >> temp_str;
		ans += "44=" + temp_str + ";";
		ss >> temp_str;
		ans += "32=" + temp_str + ";";
		ss.clear();
		ss << randint();
		ss >> temp_str;
		ans += "11=" + temp_str + ";";
	}
	else if (temp_str == "sell")
	{
		ans += "35=D;40=s;";
		ss >> temp_str;
		ans += "44=" + temp_str + ";";
		ss >> temp_str;
		ans += "32=" + temp_str + ";";
		ss.clear();
		ss << randint();
		ss >> temp_str;
		ans += "11=" + temp_str + ";";
	}
	else if (temp_str == "cancel")
	{
		ans += "35=F;";
		ss >> temp_str;
		ans += "11=" + temp_str + ";";
	}
	ans += "0=testClient;";
	return ans;
}
