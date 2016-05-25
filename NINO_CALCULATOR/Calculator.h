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
		std::string							Analyze(const AST& ast);
		float								Calculate(std::shared_ptr<AST> node, const std::map<std::string, float>& varList);
		void								Run();

	public:
		void								AddVar(const AST& ast, std::map<std::string, float>& varList);
		bool								HasVar(const std::string& varName, const std::map<std::string, float>& varList);
		std::pair<std::string, float>		FindVar(const std::string& varName, const std::map<std::string, float>& varList);

	public:
		std::vector<std::string>			GetErrorReport();

	private:
		std::map<std::string, float>		varList_;
		std::string							input_;
		std::vector<std::string>			errorReport_;
		AST									ast_;

	};

	inline bool Calculator::Calculator::HasVar(const std::string& varName, const std::map<std::string, float>& varList)
	{
		return (varList.find(varName) != varList.end());
	}

	inline std::pair<std::string, float> Calculator::FindVar(const std::string& varName, const std::map<std::string, float>& varList)
	{
		return *(varList.find(varName));
	}

	inline std::vector<std::string> Calculator::GetErrorReport()
	{
		return errorReport_;
	}


}


