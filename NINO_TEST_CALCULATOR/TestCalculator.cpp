#include "stdafx.h"
#include "CppUnitTest.h"
#include "Calculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <algorithm>

using std::vector;
using std::string;
using std::map;
using std::make_shared;
using namespace calculator;

namespace NINO_TEST_CALCULATOR
{
	TEST_CLASS(TestCalculator)
	{
		TEST_METHOD(Test_Calculate)
		{
			Parser	parser;
			Calculator cal;

			// 5
			Assert::AreEqual(cal.Calculate(make_shared<AST>(AST(Token(TokenType::INT, 5)))), 5.0f,	L"5 -> 5.0f)");

			// 5 * 1
			parser = Parser(Scanner("5*1").GetTokenList());																				
			Assert::AreEqual(cal.Calculate(make_shared<AST>(parser.GetAST())),  5.0f,	L"5 * 1 -> 5.0f");

			// (7 + 2) / 5
			parser = Parser(Scanner("(7+2)/5").GetTokenList());
			Assert::AreEqual(cal.Calculate(make_shared<AST>(parser.GetAST())),  1.8f,	L"(7 + 2) / 5 -> 1.8f");

			// 5.1 + 3.1
			parser = Parser(Scanner("5.1+3.1").GetTokenList());
			Assert::AreEqual(cal.Calculate(make_shared<AST>(parser.GetAST())), 8.2f,	L"5.1 + 3.1 -> 8.2f");

			// 5.1 + 3
			parser = Parser(Scanner("5.1+3").GetTokenList());
			Assert::AreEqual(cal.Calculate(make_shared<AST>(parser.GetAST())), 8.1f,	L"5.1 + 3 = 8.1f");

		}

		TEST_METHOD(Test_Equation)
		{
			Parser	parser;
			Calculator cal;

			// x + 5 = 10
			parser = Parser(Scanner("x+5=10").GetTokenList());
			Assert::AreEqual(cal.Equation(std::make_shared<AST>(parser.GetAST())), std::string("x=5.000000"),
				L"x + 5 = 10 -> x = 5.000000");

			// x * 5 = 11 - 1
			parser = Parser(Scanner("x*5=11-1").GetTokenList());																					
			Assert::AreEqual(cal.Equation(std::make_shared<AST>(parser.GetAST())), std::string("x=2.000000"),
				L"x * 5 = 11 - 1 -> x = 2.000000");
	
		}

		TEST_METHOD(Test_Equation_LeftAndRight)
		{
			Calculator cal;
			Parser	parser;
			std::vector<Token> tokenList;
			std::shared_ptr<AST> node;
			std::string varName;

			std::vector<Token> resultList;
			std::vector<Token> correctList;

			// x + 5 = 10
			tokenList = { Token(TokenType::VAR, "x"), Token(TokenType::ADD), Token(TokenType::INT, 5),
				Token(TokenType::ASSIGNMENT), Token(TokenType::INT, 10) };																					// for GetNodeTerm
			node = make_shared<AST>(parser.GetNodeStat(tokenList.begin(), tokenList.end()));
			
			cal.EquationForRight(node->right_, resultList, varName);
			cal.EquationForLeft(node->left_,  resultList, varName);
			correctList = { Token(TokenType::INT, 10), Token(TokenType::SUB), Token(TokenType::INT, 5) };
			Assert::IsTrue(std::equal(resultList.begin(), resultList.end(), correctList.begin(), correctList.end()),
				L"x + 5 = 10 -> x = 10 - 5");

			// x * 5 = 10 - 1
			tokenList = { Token(TokenType::VAR, "x"), Token(TokenType::MUL), Token(TokenType::INT, 5),
				Token(TokenType::ASSIGNMENT), Token(TokenType::INT, 10), Token(TokenType::SUB), Token(TokenType::INT, 1) };																					// for GetNodeTerm
			node = make_shared<AST>(parser.GetNodeStat(tokenList.begin(), tokenList.end()));
			resultList = std::vector<Token>();
			varName = std::string("");

			cal.EquationForRight(node->right_, resultList, varName);
			cal.EquationForLeft(node->left_, resultList, varName);
			correctList = { Token(TokenType::LEFT_PAR), Token(TokenType::INT, 10), Token(TokenType::SUB), Token(TokenType::INT, 1), Token(TokenType::RIGHT_PAR),
			Token(TokenType::DIV), Token(TokenType::INT, 5) };
			Assert::IsTrue(std::equal(resultList.begin(), resultList.end(), correctList.begin(), correctList.end()),
				L"x * 5 = 10 - 1 -> x = (10 - 1) / 5");

		


		}

		//TEST_METHOD(Test_AddVar)
		//{
		//	Calculator cal;
		//	map<string, float> varList;
		//	Scanner scanner("var = 5.0");
		//	Parser parser(scanner.GetTokenList());

		//	auto test = parser.GetAST();
		//	cal.AddVar(parser.GetAST(), varList);
		//	Assert::AreEqual(varList.find("var")->first == "var", true, L"var = 5.0  ->  var");
		//	Assert::AreEqual(varList.find("var")->second == 5.0f, true, L"var = 5.0  ->  5.0");
		//	
		//}
	};
}