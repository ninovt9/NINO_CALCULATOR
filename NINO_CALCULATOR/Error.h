#pragma once


#include <iostream>
#include <string>
#include <vector>

namespace calculator
{
	void ErrorToken(const std::string& msg, std::vector<std::string>&  errorReport);
	void ErrorSyntax(const std::string& msg, std::vector<std::string>&  errorReport);
	void ErrorName(const std::string& msg, std::vector<std::string>&  errorReport);
}
