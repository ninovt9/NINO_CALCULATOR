#include "stdafx.h"
#include "Expression.h"

using std::string;

namespace calculator
{

	Expression::Expression(const string &expression)
	{
		Parser parser(expression);
		ast_ = parser.GetAST();
		result_ = Calculate(std::make_shared<AST>(ast_));
	}

	float Expression::Calculate(std::shared_ptr<AST> node)
	{
		if (node != nullptr)
		{
			switch (node->token_.GetType())
			{
			case TokenType::ADD:
				return Calculate(node->left_) + Calculate(node->right_);
				break;
			case TokenType::SUB:
				return Calculate(node->left_) - Calculate(node->right_);
				break;
			case TokenType::MUL:
				return Calculate(node->left_) * Calculate(node->right_);
				break;
			case TokenType::DIV:
				return Calculate(node->left_) / Calculate(node->right_);
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


