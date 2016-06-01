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


		//// iterating through the AST
		//if (node != nullptr)
		//{
		//	EquationForLeft(node->left_, tokenList, var);
		//	if (node->token_.GetType() == TokenType::VAR)
		//	{
		//		var = node->token_;
		//	}
		//	else if (node->token_.GetType() != TokenType::ASSIGNMENT)
		//	{
		//		if (node->token_.GetType() == TokenType::ADD)
		//		{
		//			tokenList.push_back(TokenType::SUB);
		//		}
		//		else if (node->token_.GetType() == TokenType::SUB)
		//		{
		//			tokenList.push_back(TokenType::ADD);
		//		}
		//		else if (node->token_.GetType() == TokenType::MUL)
		//		{
		//			AddPar(tokenList);
		//			tokenList.push_back(TokenType::DIV);
		//		}
		//		else if (node->token_.GetType() == TokenType::DIV)
		//		{
		//			AddPar(tokenList);
		//			tokenList.push_back(TokenType::MUL);
		//		}
		//		else
		//		{
		//			tokenList.push_back(node->token_);
		//		}
		//	}
		//	EquationForLeft(node->right_, tokenList, var);
			
		//}
	

		//if (node != nullptr)
		//{
		//	// AddNode(node, newAst);
		//	Equation(node->right_, newAst);
		//	Equation(node->left_, newAst);



		//	//if (node->token_ == TokenType::ASSIGNMENT)
		//	//{
		//	//	// AddNode(node, newAst);
		//	//	Equation(node->right_, newAst);
		//	//	Equation(node->left_, newAst);
		//	//}
		//	//else if (node->token_.GetType() == TokenType::INT || 
		//	//	node->token_.GetType() == TokenType::FLOAT)
		//	//{
		//	//	
		//	//}
		//	//else if (node->token_.GetType() == TokenType::ADD ||
		//	//	node->token_.GetType() == TokenType::SUB ||
		//	//	node->token_.GetType() == TokenType::MUL ||
		//	//	node->token_.GetType() == TokenType::DIV)
		//	//{
		//	//	
		//	//}
		//}
	


	//void Calculator::AddNode(std::shared_ptr<AST> root, std::shared_ptr<AST> node)
	//{
	//	if (root == nullptr)
	//	{
	//		root = node;
	//	}
	//	else if (node->token_.GetType() == TokenType::VAR)
	//	{

	//	}
	//	else if (node->token_.GetType() == TokenType::ADD ||
	//		node->token_.GetType() == TokenType::SUB ||
	//		node->token_.GetType() == TokenType::MUL ||
	//		node->token_.GetType() == TokenType::DIV)
	//	{
	//		if (root->token_.GetType() == TokenType::INT ||
	//			root->token_.GetType() == TokenType::FLOAT)
	//		{
	//			auto temp = root;
	//			node->left_ = temp;
	//			root = node;
	//		}
	//	}
	//	else if (node->token_.GetType() == TokenType::INT ||
	//		root->token_.GetType() == TokenType::FLOAT)
	//	{
	//		
	//	}
	//	else 
	//	{
	//		AddNode(root->right_, node);	
	//	}
	//}

}


