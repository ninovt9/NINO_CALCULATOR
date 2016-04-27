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


	//由getToken改为vector的iter实现...这么看原来的代码全废了。。。
	//所以vczh说的很有道理，应该针对函数测试，而不是class的实现
	//妈蛋， 重构之前先不写unit class了！



	public:
		Parser(const std::string &expression);

	public:
		AST GetAST();
		AST GetNodeExp(std::vector<Token>::iterator iter);
		AST GetNodeTerm(std::vector<Token>::iterator iter);
		AST GetNodeFactor(std::vector<Token>::iterator iter);


		//AST GetAST();
		//AST GetNodeExp(Token token);		
		//AST GetNodeTerm(Token token);		
		//AST GetNodeFactor(Token token);	

	private:
		AST ast_;
		Scanner scanner_;		
		std::vector<Token> tokenList_;
	};
}



