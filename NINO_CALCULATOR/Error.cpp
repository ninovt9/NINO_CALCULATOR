#include "stdafx.h"
#include "Error.h"


using std::string;
using std::cerr;
using std::endl;

namespace calculator
{
	void ErrorToken(const string& msg, string& errorReport)
	{
		errorReport += "TokenError: " + msg + "\n";
	}

	void ErrorSyntax(const string& msg, string& errorReport)
	{
		errorReport += "SyntaxError: " + msg + "\n";
	}
}