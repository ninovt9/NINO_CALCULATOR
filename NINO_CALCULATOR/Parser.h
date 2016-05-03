#pragma once

#include "Token.h"
#include "Scanner.h"

#include <vector>
#include <memory>




namespace calculator
{
	class AST
	{
	public:
		AST();
		AST(Token root);
		AST(AST left, Token root, AST right);

	public:
		std::shared_ptr<AST> left_;
		std::shared_ptr<AST> right_;
		Token token_;
	};


	class Parser
	{
	public:
		Parser();
		Parser(const std::string &expression);

	public:
		AST GetAST();
		AST GetNodeExp(std::vector<Token>::iterator &iter, std::vector<Token>::iterator &end);
		AST GetNodeTerm(std::vector<Token>::iterator &iter, std::vector<Token>::iterator &end);
		AST GetNodeFactor(std::vector<Token>::iterator &iter, std::vector<Token>::iterator &end);

	public:
		float calculate(std::shared_ptr<AST> node);

	private:
		AST ast_;
		Scanner scanner_;		
		std::vector<Token> tokenList_;
	};
}



