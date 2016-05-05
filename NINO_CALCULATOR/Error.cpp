#include "stdafx.h"
#include "Error.h"


using std::string;
using std::cerr;
using std::endl;

namespace calculator
{
	void ErrorToken(const string& msg)
	{
		cerr << "TokenError: " << msg << endl;
	}

	void ErrorSyntax(const string& msg)
	{
		cerr << "SyntaxError: " << msg << endl;
	}
}