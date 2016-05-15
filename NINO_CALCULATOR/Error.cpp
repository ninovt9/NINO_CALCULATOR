#include "stdafx.h"
#include "Error.h"


using std::string;
using std::cerr;
using std::endl;

namespace calculator
{
	void ErrorToken(const string& msg, std::vector<std::string>& errorReport)
	{
		errorReport.push_back("TokenError: " + msg + "\n");
	}

	void ErrorSyntax(const string& msg, std::vector<std::string>& errorReport)
	{
		errorReport.push_back("SyntaxError: " + msg + "\n");
	}
}