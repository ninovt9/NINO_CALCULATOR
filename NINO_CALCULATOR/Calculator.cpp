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
			std::cout << ">>>";
			std::getline(std::cin, input_);

			Scanner scanner(input_);
			Parser parser(scanner.GetTokenList());
			errorReport_ = scanner.GetErrorReport();
			if (errorReport_.size() != 0)
			{
				std::cout << errorReport_[0] << std::endl;
			}
			else
			{
				ast_ = parser.GetAST();
				errorReport_ = parser.GetErrorReport();

				if (errorReport_.size() != 0)
				{
					std::cout << errorReport_[0] << std::endl;
				}
				else
				{
					auto result = Analyze(ast_);
					if (errorReport_.size() != 0)
					{
						std::cout << errorReport_[0] << std::endl;
					}
					else
					{
						std::cout << result << std::endl;
					}
				}
			}

			
		}
	}

	void Calculator::AddVar(const AST& ast, map<string, float>& varList)
	{
		auto varName = ast.left_->token_.GetVarName();
		auto varValue = Calculate(ast.right_, varList_);

		varList.insert(std::pair<string, float>(varName, varValue));
	}


	std::string Calculator::Analyze(const AST& ast)
	{
		std::string print;
		if (ast.token_ == TokenType::ASSIGNMENT)
		{
			AddVar(ast, varList_);
		}
		else
		{
			// µ÷ÓÃCalculator()
			print += std::to_string(Calculate(std::make_shared<AST>(ast), varList_));
		}

		return print;
	}

	float Calculator::Calculate(std::shared_ptr<AST> node, const std::map<std::string, float>& varList)
	{
		if (node != nullptr)
		{
			switch (node->token_.GetType()) 
			{
			case TokenType::ADD:
				return Calculate(node->left_, varList) + Calculate(node->right_, varList);
				break;
			case TokenType::SUB:
				return Calculate(node->left_, varList) - Calculate(node->right_, varList);
				break;
			case TokenType::MUL:
				return Calculate(node->left_, varList) * Calculate(node->right_, varList);
				break;
			case TokenType::DIV:
				return Calculate(node->left_, varList) / Calculate(node->right_, varList);
				break;
			case TokenType::INT:
				return static_cast<float>(node->token_.GetIntValue());
				break;
			case TokenType::FLOAT:
				return (node->token_.GetFloatValue());
				break;
			case TokenType::VAR:
				if (HasVar(node->token_.GetVarName(), varList))
				{
					return FindVar(node->token_.GetVarName(), varList).second;
				}
				else
				{
					// NameError: name X is not defined
					ErrorName("name '" + node->token_.GetVarName() + "' is not defined",
						errorReport_);
				}
				break;
			}
		}
		else
		{
			// error
			
		}

	}
}


