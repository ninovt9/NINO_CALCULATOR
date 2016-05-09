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

	bool Expression::IsAstEqual(std::shared_ptr<AST> base, std::shared_ptr<AST> other)
	{
		if (base == nullptr || other == nullptr)
		{
			return (base == other);
		}
		else if (base->token_ == other->token_)
		{
			// left node
			if (IsAstEqual(base->left_, other->left_) == true && IsAstEqual(base->right_, other->right_) == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	


}


