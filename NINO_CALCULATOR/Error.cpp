#include "stdafx.h"
#include "Error.h"


using std::string;
using std::cerr;
using std::endl;

namespace calculator
{
	void ErrorToken(const string& msg, std::vector<std::string>& errorReport)
	{
		errorReport.push_back("TokenError: " + msg);
	}

	void ErrorSyntax(const string& msg, std::vector<std::string>& errorReport)
	{
		errorReport.push_back("SyntaxError: " + msg);
	}

	void ErrorName(const std::string& msg, std::vector<std::string>&  errorReport)
	{
		errorReport.push_back("NameError: " + msg);
	}

}