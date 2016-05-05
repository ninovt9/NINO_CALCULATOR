#include "stdafx.h"
#include "Parser.h"

using std::vector;

namespace calculator
{

	AST::AST() : left_(nullptr), right_(nullptr)
	{

	}

	AST::AST(const Token &root) :token_(root), left_(nullptr), right_(nullptr)
	{

	}

	AST::AST(const AST &left, const Token &root, const AST &right) 
		: token_(root), left_(std::make_shared<AST>(left)), right_(std::make_shared<AST>(right))
	{

	}

	AST::AST(const AST& other)
	{
		left_ = other.left_;
		right_ = other.right_;
		token_ = other.token_;
	}

	AST& AST::operator=(const AST& other)
	{
		left_ = other.left_;
		right_ = other.right_;
		token_ = other.token_;
		return *this;
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
				// operator¤Îtoken
				auto operaToken = ++iter;
				// term +- term
				ast = AST(ast, *operaToken, GetNodeTerm(++iter, end));
			}
			else
			{
				break;
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
				// operator¤Îtoken
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
				if ((iter + 1)->GetType() == TokenType::RIGHT_PAR)
				{
					// delete parenteses
					iter++;	
				}
				else
				{
					// error
				}
			}
		}
		else
		{
			//error£¬ ÔÝÊ±²»Ð´
		}

		return ast;
	}

	float Parser::calculate(std::shared_ptr<AST> node)
	{
		if (node != nullptr)
		{
			switch (node->token_.GetType())
			{
			case TokenType::ADD:
				return calculate(node->left_) + calculate(node->right_);
				break;
			case TokenType::SUB:
				return calculate(node->left_) - calculate(node->right_);
				break;
			case TokenType::MUL:
				return calculate(node->left_) * calculate(node->right_);
				break;
			case TokenType::DIV:
				return calculate(node->left_) / calculate(node->right_);
				break;
			case TokenType::INT:
				return static_cast<float>(node->token_.GetIntValue());
				break;
			}
		}
		else
		{
			// error
		}


	}
}