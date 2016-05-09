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
		AST(const Token &root);
		AST(const AST &left, const Token &root, const AST &right);

	public:
		AST(const AST& other);
		AST& operator=(const AST& other);

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

	//public:
	//	const AST& GetRoot();

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

	//const AST& Parser::GetRoot()
	//{
	//	return ast_;
	//}
}



