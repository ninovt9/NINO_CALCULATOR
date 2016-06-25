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

			// 2x + 1 = 3
			parser = Parser(Scanner("2x+1=3").GetTokenList());
			Assert::AreEqual(cal.Equation(std::make_shared<AST>(parser.GetAST())), std::string("x=1.000000"),
				L"2x + 1 = 3 -> x = 1.000000");

			// 1 + x = 10
			parser = Parser(Scanner("1+x=10").GetTokenList());
			Assert::AreEqual(cal.Equation(std::make_shared<AST>(parser.GetAST())), std::string("x=9.000000"),
				L"1 + x = 10 -> x = 9.000000");
	
		}



		TEST_METHOD(Test_EquationForLeft)
		{
			Calculator cal;
			Parser parser;
			

			std::vector<Token> resultList;
			std::vector<Token> correctList;
			Token var;

			// x + 5 = 10
			parser = Parser(Scanner("x+5=10").GetTokenList());
			cal.EquationForLeft(std::make_shared<AST>(parser.GetAST())->left_, resultList, var);
			correctList = Scanner("0.0+5").GetTokenList();

			Assert::IsTrue(std::equal(resultList.begin(), resultList.end(), correctList.begin(), correctList.end()),
				L"x + 5 = 10 -> 0.0 + 5");
			Assert::IsTrue(var == Token(TokenType::VAR, "x", 1.0f),
				L"x + 5 = 10 -> x");



			resultList = std::vector<Token>();

			// x * 5 = 10 - 1
			parser = Parser(Scanner("x*5=10-1").GetTokenList());
			cal.EquationForLeft(std::make_shared<AST>(parser.GetAST())->left_, resultList, var);
			correctList = Scanner("1.0*5").GetTokenList();

			Assert::IsTrue(std::equal(resultList.begin(), resultList.end(), correctList.begin(), correctList.end()),
				L"x * 5 = 10 - 1 -> 1.0 * 5");
			Assert::IsTrue(var == Token(TokenType::VAR, "x", 1.0f),
				L"x * 5 = 10 - 1 -> x");

		}

		TEST_METHOD(Test_EquationForRight)
		{
			Calculator cal;
			Parser parser;


			std::vector<Token> resultList;
			std::vector<Token> correctList;
			Token var;

			// x + 5 = 10
			parser = Parser(Scanner("x+5=10").GetTokenList());
			cal.EquationForRight(std::make_shared<AST>(parser.GetAST())->right_, resultList, var);
			correctList = Scanner("10").GetTokenList();

			Assert::IsTrue(std::equal(resultList.begin(), resultList.end(), correctList.begin(), correctList.end()),
				L"x + 5 = 10 -> 10");


			resultList = std::vector<Token>();

			// x * 5 = 10 - 1
			parser = Parser(Scanner("x*5=10-1").GetTokenList());
			cal.EquationForRight(std::make_shared<AST>(parser.GetAST())->right_, resultList, var);
			correctList = Scanner("10-1").GetTokenList();

			Assert::IsTrue(std::equal(resultList.begin(), resultList.end(), correctList.begin(), correctList.end()),
				L"x * 5 = 10 - 1 -> 10-1");


		}

		TEST_METHOD(Test_MergeVarList)
		{
			Calculator cal;

			// 3x + 2x
			auto varList = Scanner("3x 2x").GetTokenList();
			auto resultList = cal.MergeVarList(varList);

			Assert::IsTrue(resultList.find("x")->second == Token(TokenType::VAR, "x", 5.0f),
				L"3x + 2x -> 5x");
			Assert::AreEqual(resultList.size(), static_cast<size_t>(1),
				L"3x + 2x .size -> 1");
		}

		TEST_METHOD(Test_VarListToString)
		{
			Calculator cal;

			// 5x
			auto varList = cal.MergeVarList(Scanner("5x").GetTokenList());

			auto test = cal.VarListToString(varList);
			Assert::IsTrue(cal.VarListToString(varList) == std::string("5x"),
				L"5x -> 5x");
		}


	};
}