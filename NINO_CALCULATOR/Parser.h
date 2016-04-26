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
	// expression : term { ("+" | "-") term }
	// term : factor { ("*" | "/") factor }
	// factor : number | "(" expression ")" 

	public:
		Parser(const std::string &expression);

	public:
		AST CreateAST();
		AST RuleExp(Token token);		
		AST RuleTerm(Token token);		
		AST RuleFactor(Token token);	

	private:
		AST ast_;
		Scanner scanner_;		
	};
}



