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
		tokenList_ = scanner_.GetTokenList();
		ast_ = GetAST();
	}

	AST Parser::GetAST()
	{
		return GetNodeExp(tokenList_.begin());
	}

	AST Parser::GetNodeExp(vector<Token>::iterator iter)
	{
		// expression : term { ("+" | "-") term };	
		AST ast = AST();

		// only term
		ast = GetNodeTerm(iter);
		
		for (;;)
		{
			// peek����/���ŵ������->��λ
			if ((iter + 1)->GetType() == TokenType::ADD
				|| (iter + 1)->GetType() == TokenType::SUB)
			{
				// ���operator��token����λ
				auto operaToken = iter++;
				// term +- term
				ast = AST(ast, *operaToken, GetNodeTerm(iter++));
			}
			else
			{
				break;
			}
		}
		
		return ast;

		//	iter++;
		//	auto operaToken = *iter;

		//	if (operaToken.GetType() == TokenType::ADD 
		//		|| operaToken.GetType() ==  TokenType::SUB)
		//	{
		//		// term +- term
		//		ast = AST(ast, operaToken, GetNodeTerm(iter++));
		//	}
		//	else
		//	{
		//		break;
		//		// error�� ��ʱ��д
		//	} 
		//}

		// return ast;
	}

	AST Parser::GetNodeTerm(vector<Token>::iterator iter)
	{
		// term : factor { ("*" | "/") factor }
		AST ast = AST();

		// only factor
		ast = GetNodeFactor(iter);

		for (;;)
		{
			// peek����/���ŵ������->��λ
			if ((iter + 1)->GetType() == TokenType::MUL
				|| (iter + 1)->GetType() == TokenType::DIV)
			{
				// ���operator��token����λ
				auto operaToken = iter++;
				// factor */ factor
				ast = AST(ast, *operaToken, GetNodeFactor(iter++));
			}
			else
			{
				break;
			}
		}

		return ast;

		//for (;;)
		//{
		//	iter++;
		//	auto operaToken = *iter;

		//	if (operaToken.GetType() == TokenType::MUL
		//		|| operaToken.GetType() == TokenType::DIV)
		//	{
		//		// factor */ factor
		//		ast = AST(ast, operaToken, GetNodeFactor(iter++)));
		//	}
		//	else
		//	{
		//		break;
		//		//error�� ��ʱ��д
		//	}

		//	
		//}

		//return ast;
	}

	AST Parser::GetNodeFactor(vector<Token>::iterator iter)
	{
		// factor: number | "(" expression ")"
		AST ast = AST();
	
		//���1������
		if (iter->GetType() == TokenType::INT)
		{
			ast = AST(*iter);
		}
		//���2������
		else if (iter->GetType() == TokenType::LEFT_PAR)
		{
			iter++;	//get expression
			if (iter->GetType() == TokenType::INT)
			{
				ast = GetNodeExp(iter);

				//�ж�������
				if (iter->GetType() != TokenType::RIGHT_PAR)
				{
					//error, ����д
				}
			}
		}
		else
		{
			//error�� ��ʱ��д
		}

		return ast;
	}
}