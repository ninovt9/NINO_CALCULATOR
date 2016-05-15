#pragma once

#include "Expression.h"

#include <map>
#include <iostream>


namespace calculator
{
	class Calculator
	{
	public:
		Calculator();
	public:
		std::string Analyze(const AST& ast);
		void Assigned(const AST& ast, std::map<std::string, float>& varList_);
		float Calculate(std::shared_ptr<AST> node);
		void Run();
	private:
		std::map<std::string, float> varList_;
		std::string input_;
		std::vector<std::string> errorReport_;
		AST ast_;

	};
}


