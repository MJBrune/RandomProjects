#ifndef HELP_FUNCS
#define HELP_FUNCS
#include <sstream>
#include <SFML/Graphics.hpp>

template<class type>
const std::string ToString(type t)
{
	std::stringstream str;
	str<<t;
	std::string ret = str.str();
	str.clear();
	str.flush();
	return ret;
}

#endif