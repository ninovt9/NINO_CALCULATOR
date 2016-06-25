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
		float								Calculate(std::shared_ptr<AST> node);
		std::string							Equation(std::shared_ptr<AST> node);
		void								Run();

	public:
		void								EquationForLeft(std::shared_ptr<AST> node, std::vector<Token>& tokenList, Token &var);
		void								EquationForLeft(std::shared_ptr<AST> node, std::vector<Token>& tokenList, Token &var, Token type);
		void								EquationForRight(std::shared_ptr<AST> node, std::vector<Token>& tokenList, Token &var);

	public:
		std::map<std::string, Token> 		MergeVarList(const std::vector<Token>& varList);
		std::string							VarListToString(const std::map<std::string, Token>& varList);
		void								AddPar(std::vector<Token>& tokenList);
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

	inline void Calculator::AddPar(std::vector<Token>& tokenList)
	{
		tokenList.insert(tokenList.begin(), Token(TokenType::LEFT_PAR));
		tokenList.push_back(Token(TokenType::RIGHT_PAR));
	}


}


