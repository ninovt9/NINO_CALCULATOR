#include "stdafx.h"
#include "CppUnitTest.h"
#include "Expression.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using std::string;
using std::vector;
using std::make_shared;
using namespace calculator;

namespace NINO_TEST_CALCULATOR
{
	TEST_CLASS(TestExpression)
	{

		TEST_METHOD(Test_Calculate)
		{
			Parser parser;
			Expression expression = Expression();
			std::shared_ptr<AST> node;
			vector<Token> tokenList;
			float result;

			// int
			node = make_shared<AST>(AST(Token(TokenType::INT, 5)));
			result = expression.Calculate(node);
			Assert::AreEqual(result, 5.0f);

			// 5 * 1
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::MUL), Token(TokenType::INT, 1) };	// 5 * 1																						// for GetNodeTerm
			node = make_shared<AST>(parser.GetNodeTerm(tokenList.begin(), tokenList.end()));
			result = expression.Calculate(node);
			Assert::AreEqual(result, 5.0f);

			// (7 + 2) / 5
			tokenList = { Token(TokenType::LEFT_PAR), Token(TokenType::INT, 7), Token(TokenType::ADD), Token(TokenType::INT, 2), Token(TokenType::RIGHT_PAR),
				Token(TokenType::DIV), Token(TokenType::INT, 5) };
			node = make_shared<AST>(parser.GetNodeExp(tokenList.begin(), tokenList.end()));
			result = expression.Calculate(node);
			Assert::AreEqual(result, 1.8f);


		}

		TEST_METHOD(Test_Class_Expression)
		{
			Expression expression = Expression();

			// 1 - 2
			expression = Expression("1-2");
			Assert::AreEqual(expression.GetResult(), -1.0f);

			// 5 + 2 * 3
			expression = Expression("5+2*3");
			Assert::AreEqual(expression.GetResult(), 11.0f);

			// (5 + 2) * 3
			expression = Expression("(5+2)*3");
			Assert::AreEqual(expression.GetResult(), 21.0f);

			// (2 + (5 + 2)) * 3
			expression = Expression("(2+(5+2))*3");
			Assert::AreEqual(expression.GetResult(), 27.0f);

			// 2 - (6 / 2)
			expression = Expression("2 - (6 / 2)");
			Assert::AreEqual(expression.GetResult(), -1.0f);

			// 5 + 1
			expression = Expression(" 5 + 1 ");
			Assert::AreEqual(expression.GetResult(), 6.0f);


		}

		TEST_METHOD(Test_Class_Operator_Add)
		{
			auto result = Expression("1+5") + Expression("10");
			Assert::AreEqual(result.GetResult(), 16.0f, L"E(1+5)+E(10)==16.0f failed");
			
			result = Expression("1*5") + Expression("12*(5+1)");
			Assert::AreEqual(result.GetResult(), 77.0f, L"E(1*5)+E(12*(5+1))==77.0f failed");

			result = Expression("1+5") - Expression("1");
			Assert::AreEqual(result.GetResult(), 5.0f, L"E(1+5)-E(1)==5.0f failed");

			result = Expression("1+5") * Expression("2");
			Assert::AreEqual(result.GetResult(), 12.0f, L"E(1+5)*E(2)==12.0f failed");

			result = Expression("1+5") / Expression("3");
			Assert::AreEqual(result.GetResult(), 2.0f, L"E(1+5)/E(3)==2.0f failed");
		}
			
	};
}
