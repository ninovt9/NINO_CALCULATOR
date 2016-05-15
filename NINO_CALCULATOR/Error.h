#pragma once


#include <iostream>
#include <string>

namespace calculator
{
	extern void ErrorToken(const std::string& msg, std::string& errorReport);
	extern void ErrorSyntax(const std::string& msg, std::string& errorReport);
}
