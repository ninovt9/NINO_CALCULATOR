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
		ast_ = AST();
	}

	Parser::Parser(const std::vector<Token>& tokenList) : tokenList_(tokenList)
	{
		ast_ = GetAST();
	}

	AST Parser::GetAST()
	{
		return GetNodeStat(tokenList_.begin(), tokenList_.end());
	}

	AST Parser::GetNodeStat(std::vector<Token>::iterator &iter,vector<Token>::iterator &end)
	{
		// statement : expression { = expression }

		AST ast;

		ast = GetNodeExp(iter, end);

		for (;;)
		{
			// out of range check
			if (iter + 1 == end)
			{
				break;
			}

			// peek
			if ((iter + 1)->GetType() == TokenType::ASSIGNMENT)
			{
				// operatorのtoken
				auto operaToken = ++iter;

				// out of range check
				if (iter + 1 != end)
				{
					// term +- term
					ast = AST(ast, *operaToken, GetNodeExp(++iter, end));
				}
				else
				{
					ErrorSyntax("invalid syntax", errorReport_);
				}

			}
			else
			{
				ErrorSyntax("invalid syntax", errorReport_);
				break;
			}
		}

		return ast;
		
	}

	AST Parser::GetNodeExp(vector<Token>::iterator &iter, vector<Token>::iterator &end)
	{
		// expression : term { ("+" | "-") term };	

		AST ast;

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

			// peek
			if ((iter + 1)->GetType() == TokenType::ADD
				|| (iter + 1)->GetType() == TokenType::SUB)
			{
				// operatorのtoken
				auto operaToken = ++iter;

				// out of range check
				if (iter + 1 != end)
				{
					// term +- term
					ast = AST(ast, *operaToken, GetNodeTerm(++iter, end));
				}
				else
				{
					ErrorSyntax("invalid syntax", errorReport_);
				}

			}
			else if ((iter + 1)->GetType() == TokenType::RIGHT_PAR)
			{
				break;
			}
			else
			{
				// 这个error只用用在最顶端的函数
				// ErrorSyntax("invalid syntax", errorReport_);
				break;
			}
		}
		
		return ast;
	}

	AST Parser::GetNodeTerm(vector<Token>::iterator &iter, vector<Token>::iterator &end)
	{
		// term : factor { ("*" | "/") factor }

		AST ast;

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
				// operatorのtoken
				auto operaToken = ++iter;
				// factor */ factor
				ast = AST(ast, *operaToken, GetNodeFactor(++iter, end));
			}
			else
			{
				//ErrorSyntax("invalid syntax", errorReport_);
				break;
			}
		}

		return ast;
	}

	AST Parser::GetNodeFactor(vector<Token>::iterator &iter, vector<Token>::iterator &end)
	{
		// assignment | number | "(" expression ")" 

		AST ast;

		// assignment
		if (iter->GetType() == TokenType::VAR)
		{
			ast = AST(*iter);
		}
		// number
		else if (iter->GetType() == TokenType::INT || iter->GetType() == TokenType::FLOAT)
		{
			ast = AST(*iter);
		}
		// parentheses
		else if (iter->GetType() == TokenType::LEFT_PAR)
		{
			//iter++;	//get expression
			if (IsNumber(*(iter+1)) || (iter+1)->GetType() == TokenType::LEFT_PAR)				// IsNumber(*iter))    
			{
				iter++;
				ast = GetNodeExp(iter, end);

				
				// out of range
				if (iter + 1 != end)
				{
					// check right parentheses
					if ((iter + 1)->GetType() == TokenType::RIGHT_PAR)
					{
						// delete parenteses
						iter++;
					}
					else
					{
						// error
						ErrorSyntax("invalid syntax", errorReport_);
					}
				}
				else
				{
					ErrorSyntax("invalid syntax", errorReport_);
				}
				

			}
			else
			{
				ErrorSyntax("invalid syntax", errorReport_);
			}
		}
		else
		{
			ErrorSyntax("invalid syntax", errorReport_);
		}

		return ast;
	}

}