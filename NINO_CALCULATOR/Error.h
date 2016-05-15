#pragma once


#include <iostream>
#include <string>
#include <vector>

namespace calculator
{
	extern void ErrorToken(const std::string& msg, std::vector<std::string>&  errorReport);
	extern void ErrorSyntax(const std::string& msg, std::vector<std::string>&  errorReport);
}
