#include "stdafx.h"
#include "Calculator.h"

using std::map;
using std::string;

namespace calculator
{
	Calculator::Calculator() : input_("")
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


	std::string Calculator::Analyze(const AST& ast)
	{
		std::string print;
		if (ast.token_ == TokenType::VAR)
		{
			print += ast.token_.GetVarName();
		}
		else if (ast.token_ == TokenType::ASSIGNMENT)
		{
			print += Equation(std::make_shared<AST>(ast));
		}
		else
		{
			// 调用Calculator()
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

	std::string Calculator::Equation(std::shared_ptr<AST> node)
	{
		std::vector<Token> tokenList;

		Token var;

		EquationForRight(node->right_, tokenList, var);

		tokenList.push_back(Token(TokenType::SUB));
		tokenList.push_back(Token(TokenType::LEFT_PAR));

		EquationForLeft(node->left_, tokenList, var);
		tokenList.push_back(Token(TokenType::RIGHT_PAR));

		Parser parser(tokenList);
		auto tree = parser.GetAST();
		auto value = std::to_string(Calculate(std::make_shared<AST>(parser.GetAST())) / var.GetCoefficient());

		return var.GetVarName() + "=" + value;
	}

	void Calculator::EquationForRight(std::shared_ptr<AST> node, std::vector<Token>& tokenList, Token &var)
	{
		// iterating through the AST
		if (node != nullptr)
		{
			EquationForRight(node->left_, tokenList, var);
			tokenList.push_back(node->token_);
			EquationForRight(node->right_, tokenList, var);
		}
	}

	void Calculator::EquationForLeft(std::shared_ptr<AST> node, std::vector<Token>& tokenList, Token &var)
	{
		EquationForLeft(node, tokenList, var, node->token_.GetType());
	}

	void Calculator::EquationForLeft(std::shared_ptr<AST> node, std::vector<Token>& tokenList, Token &var, Token type)
	{
		if (node != nullptr)
		{
			EquationForLeft(node->left_, tokenList, var, type);
			if (node->token_.GetType() == TokenType::VAR)
			{
				var = node->token_;
				if (type.GetType() == TokenType::ADD ||
					type.GetType() == TokenType::SUB)
				{	
					node->token_ = Token(TokenType::FLOAT, 0.0f);
				}
				else
				{
					node->token_ = Token(TokenType::FLOAT, 1.0f);
				}
			
			}
			tokenList.push_back(node->token_);
			EquationForLeft(node->right_, tokenList, var, type);
		}
	}

	std::map<std::string, Token> Calculator::Merg          eVarList(const std::vector<Token>& varList)
	{
		std::map<std::string, Token> resultList;
		
		for (auto each : varList)
		{
			auto iter = resultList.find(each.GetVarName());
			if (iter != resultList.end())
			{
				iter->second.AddCoefficient(each.GetCoefficient());
			}
			else
			{
				resultList.insert({ each.GetVarName(), each });
			}

		}

		return resultList;
	}

	std::string Calculator::VarListToString(const std::map<std::string, Token>& varList)
	{
		std::string result;

		for (auto each : varList)
		{
			result.append(std::string(each.first + "+"));
		}

		// 最后一个+删掉
		result.pop_back();

		return result;
	}

}


