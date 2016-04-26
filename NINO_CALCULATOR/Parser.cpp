#include "stdafx.h"
#include "Parser.h"

using std::vector;

namespace calculator
{

	AST::AST() : left_(nullptr), right_(nullptr)
	{

	}

	AST::AST(Token root) :token_(root), left_(nullptr), right_(nullptr)
	{

	}

	AST::AST(AST left, Token root, AST right) : token_(root)
	{
		left_ = std::make_shared<AST>(left);
		right_ = std::make_shared<AST>(right);
	}

}



namespace calculator
{

	Parser::Parser(const std::string &expression)
	{
		scanner_ = Scanner(expression);
		ast_ = CreateAST();
	}

	AST Parser::CreateAST()
	{
		return RuleExp(scanner_.GetNextToken());
	}

	AST Parser::RuleExp(Token token)
	{
		// expression : term { ("+" | "-") term };	
		AST ast = AST();

		// only term
		ast = RuleTerm(token);
		
		// term +- term
		for (;;)
		{
			auto operaToken = scanner_.GetNextToken();

			if (operaToken.GetType() == TokenType::ADD 
				|| operaToken.GetType() ==  TokenType::SUB)
			{
				ast = AST(ast, operaToken, RuleTerm(scanner_.GetNextToken()));
			}
			else
			{
				break;
				// error， 暂时不写
			} 
		}

		return ast;


		//auto operaToken = scanner_.GetNextToken();

		//if (operaToken.GetType() == TokenType::ADD 
		//	|| operaToken.GetType() ==  TokenType::SUB)
		//{
		//	ast = AST(ast, operaToken, RuleTerm(scanner_.GetNextToken()));
		//}
		//else
		//{
		//	// error， 暂时不写
		//} 

		//return ast;
	}

	AST Parser::RuleTerm(Token token)
	{
		// term : factor { ("*" | "/") factor }
		AST ast = AST();

		// only factor
		ast = RuleFactor(token);

		// factor */ factor

		for (;;)
		{
			auto operaToken = scanner_.GetNextToken();

			if (operaToken.GetType() == TokenType::MUL
				|| operaToken.GetType() == TokenType::DIV)
			{
				ast = AST(ast, operaToken, RuleFactor(scanner_.GetNextToken()));
			}
			else
			{
				break;
				//error， 暂时不写
			}

			
		}

		return ast;

		//// factor */ factor
		//auto operaToken = scanner_.GetNextToken();

		//if (operaToken.GetType() == TokenType::MUL
		//	|| operaToken.GetType() == TokenType::DIV)
		//{
		//	ast = AST(ast, operaToken, RuleFactor(scanner_.GetNextToken()));
		//}
		//else
		//{
		//	//error， 暂时不写
		//}

		//return ast;
	}

	AST Parser::RuleFactor(Token token)
	{
		// factor: number | "(" expression ")"

		AST ast = AST();
	
		//情况1：数字
		if (token.GetType() == TokenType::INT)
		{
			ast = AST(token);
		}
		//情况2：括号
		else if (token.GetType() == TokenType::LEFT_PAR)
		{
			token = scanner_.GetNextToken();
			if (token.GetType() == TokenType::INT 
				&& scanner_.GetNextToken().GetType() == TokenType::RIGHT_PAR)
			{
				ast = RuleExp(token);
			}
			else
			{
				//error， 暂时不写
			}
		}
		else
		{
			//error， 暂时不写
		}

		return ast;
	}
}