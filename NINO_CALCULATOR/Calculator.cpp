#include "stdafx.h"
#include "Calculator.h"

using std::map;
using std::string;

namespace calculator
{
	Calculator::Calculator():buffer_("")
	{

	}

	void Calculator::Run()
	{
		for (;;)
		{
			std::getline(std::cin, input_);
			ast_ = Parser(input_).GetAST();
			Analyze(ast_);

			std::cout << ">>>" << buffer_ << std::endl;
			buffer_ = "";
		}
	}

	void Calculator::Assigned(const AST& ast, map<string, float>& varList)
	{
		auto varName = ast.left_->token_.GetVarName();
		auto varValue = Calculate(ast.right_);

		varList.insert(std::pair<string, float>(varName, varValue));
	}

	void Calculator::Analyze(const AST& ast)
	{
		if (ast.token_ == TokenType::ASSIGNED)
		{
			Assigned(ast, varList_);
		}
		else
		{
			// µ÷ÓÃCalculator()
			buffer_ += std::to_string(Calculate(std::make_shared<AST>(ast)));
		}
	}

	float Calculator::Calculate(std::shared_ptr<AST> node)
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
			case TokenType::FLOAT:
				return (node->token_.GetFloatValue());
				break;
			}
		}
		else
		{
			// error
		}

	}
}


