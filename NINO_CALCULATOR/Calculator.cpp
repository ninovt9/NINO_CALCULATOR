#include "stdafx.h"
#include "Calculator.h"

using std::map;
using std::string;

namespace calculator
{
	Calculator::Calculator(): input_("")
	{

	}

	void Calculator::Run()
	{
		for (;;)
		{
			std::getline(std::cin, input_);

			Scanner scanner(input_);
			Parser parser(scanner.GetTokenList());
			errorReport_ = scanner.GetErrorReport();
			if (errorReport_.size() != 0)
			{
				std::cout << errorReport_[0];
			}
			else
			{
				ast_ = parser.GetAST();
				errorReport_ = parser.GetErrorReport();

				if (errorReport_.size() != 0)
				{
					std::cout << errorReport_[0];
				}
				else
				{
					std::cout << ">>>" << Analyze(ast_) << std::endl;
				}
			}

			
		}
	}

	void Calculator::Assigned(const AST& ast, map<string, float>& varList)
	{
		auto varName = ast.left_->token_.GetVarName();
		auto varValue = Calculate(ast.right_);

		varList.insert(std::pair<string, float>(varName, varValue));
	}

	std::string Calculator::Analyze(const AST& ast)
	{
		std::string print;
		if (ast.token_ == TokenType::ASSIGNED)
		{
			Assigned(ast, varList_);
		}
		else
		{
			// µ÷ÓÃCalculator()
			print += std::to_string(Calculate(std::make_shared<AST>(ast)));
		}

		return print;
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


