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
	Parser::Parser()
	{
		scanner_ = Scanner("");
		ast_ = AST();
	}

	Parser::Parser(const std::string &expression)
	{
		scanner_ = Scanner(expression);
		tokenList_ = scanner_.GetTokenList();
		ast_ = GetAST();
	}

	AST Parser::GetAST()
	{
		return GetNodeExp(tokenList_.begin(), tokenList_.end());
	}

	AST Parser::GetNodeExp(vector<Token>::iterator &iter, vector<Token>::iterator &end)
	{
		// expression : term { ("+" | "-") term };	

		AST ast = AST();

		// only term
		// descent
		ast = GetNodeTerm(iter, end);
		
		for (;;)
		{
			// out of range check
			if (iter + 1 == end)
			{
				break;
			}

			// pee
			if ((iter + 1)->GetType() == TokenType::ADD
				|| (iter + 1)->GetType() == TokenType::SUB)
			{
				// operator§Œtoken
				auto operaToken = ++iter;
				// term +- term
				ast = AST(ast, *operaToken, GetNodeTerm(++iter, end));
			}
			else
			{
				// descent
				// ast = GetNodeFactor(iter, end);
			}
		}
		
		return ast;
	}

	AST Parser::GetNodeTerm(vector<Token>::iterator &iter, vector<Token>::iterator &end)
	{
		// term : factor { ("*" | "/") factor }

		AST ast = AST();

		// only factor
		ast = GetNodeFactor(iter, end);

		for (;;)
		{
			// out of range check
			if (iter + 1 == end)
			{
				break;
			}

			// peek
			if ((iter + 1)->GetType() == TokenType::MUL
				|| (iter + 1)->GetType() == TokenType::DIV)
			{
				// operator§Œtoken
				auto operaToken = ++iter;
				// factor */ factor
				ast = AST(ast, *operaToken, GetNodeFactor(++iter, end));
			}
			else
			{
				break;
			}
		}

		return ast;
	}

	AST Parser::GetNodeFactor(vector<Token>::iterator &iter, vector<Token>::iterator &end)
	{
		// factor: number | "(" expression ")"

		AST ast = AST();
	
		// number
		if (iter->GetType() == TokenType::INT)
		{
			ast = AST(*iter);
		}
		// parentheses
		else if (iter->GetType() == TokenType::LEFT_PAR)
		{
			iter++;	//get expression
			if (iter->GetType() == TokenType::INT)
			{
				ast = GetNodeExp(iter, end);

				// check right parentheses
				if (iter->GetType() != TokenType::RIGHT_PAR)
				{
					//error, ¿¡µ√–¥
				}
			}
		}
		else
		{
			//error£¨ ‘› ±≤ª–¥
		}

		return ast;
	}
}