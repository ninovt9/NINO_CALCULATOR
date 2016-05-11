#pragma once

#include "Expression.h"

#include <map>


namespace calculator
{
	class Calculator
	{
	public:
		Calculator();
	public:
		void Run();
	private:
		std::map<std::string, Token> varList_;

	};
}


