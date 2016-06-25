#include "stdafx.h"
#include "CppUnitTest.h"
#include "Token.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace calculator;

namespace NINO_TEST_CALCULATOR
{
	TEST_CLASS(TestToken)
	{
	public:
		TEST_METHOD(Test_Init)
		{
			Token token;

			// operator
			token = Token(TokenType::ADD);
			Assert::AreEqual((token.GetType() == TokenType::ADD),		true,		L"+ -> type");
			Assert::AreEqual((token.GetIntValue() == 0),				true,		L"+ -> intValue");
			Assert::AreEqual((token.GetFloatValue() == 0.0f),			true,		L"+ -> floatValue");
			Assert::AreEqual((token.GetVarName() == ""),				true,	    L"+ -> text");

			token = Token(TokenType::ASSIGNMENT);
			Assert::AreEqual((token.GetType() == TokenType::ASSIGNMENT),	true,		L"= -> type");
			Assert::AreEqual((token.GetIntValue() == 0),				true,		L"= -> intValue");
			Assert::AreEqual((token.GetFloatValue() == 0.0f),			true,	    L"= -> floatValue");
			Assert::AreEqual((token.GetVarName() == ""),				true,		L"= -> text");

			// int
			token = Token(TokenType::INT, 5);
			Assert::AreEqual((token.GetType() == TokenType::INT),		true,		L"5 -> type");
			Assert::AreEqual((token.GetIntValue() == 5),				true,		L"5 -> intValue");
			Assert::AreEqual((token.GetFloatValue() == 0.0f),			true,		L"5 -> floatValue");
			Assert::AreEqual((token.GetVarName() == ""),				true,		L"5 -> text");

			// float
			token = Token(TokenType::FLOAT, 6.0f);
			Assert::AreEqual((token.GetType() == TokenType::FLOAT),		true,		L"6.0f -> type");
			Assert::AreEqual((token.GetIntValue() == 0),				true,	    L"6.0f -> intValue");
			Assert::AreEqual((token.GetFloatValue() == 6.0f),			true,		L"6.0f -> floatValue");
			Assert::AreEqual((token.GetVarName() == ""),				true,		L"6.0f ->  text");

			// var
			token = Token(TokenType::VAR, "each", 1.0f);
			Assert::AreEqual((token.GetType() == TokenType::VAR),		true,		L"var:each ->  type");
			Assert::AreEqual((token.GetIntValue() == 0),				true,		L"var:each ->  intValue");
			Assert::AreEqual((token.GetFloatValue() == 0.0f),			true,		L"var:each ->  floatValue");
			Assert::AreEqual((token.GetVarName() == "each"),			true,		L"var:each ->  varName");

			// 3x
			token = Token(TokenType::VAR, "x", 3.0f);
			Assert::AreEqual((token.GetType() == TokenType::VAR),		true,		L"var:3x ->  type");
			Assert::AreEqual((token.GetIntValue() == 0),				true,		L"var:3x ->  intValue");
			Assert::AreEqual((token.GetFloatValue() == 0.0f),			true,		L"var:3x ->  floatValue");
			Assert::AreEqual((token.GetVarName() == "x"),				true,		L"var:3x ->  varName");
			Assert::AreEqual((token.GetCoefficient() == 3.0f),			true,		L"var:3x ->  coefficient");

			
		}


		TEST_METHOD(Test_OperatorEqual)
		{
			// int
			Token int_1(TokenType::INT, 1);
			Token int_2(TokenType::INT, 1);
			Token int_3(TokenType::INT, 2);
			Assert::AreEqual((int_1 == int_2), true);
			Assert::AreEqual((int_1 == int_3), false);

			// float
			Token float_1(TokenType::FLOAT, 1.0f);
			Token float_2(TokenType::FLOAT, 1.0f);
			Token float_3(TokenType::FLOAT, 2.5f);
			Assert::AreEqual((float_1 == float_2), true);
			Assert::AreEqual((float_1 == float_3), false);

			Token double_1(TokenType::FLOAT, 6.0);
			Token double_2(TokenType::FLOAT, 6.0);
			Assert::AreEqual((double_1 == double_2), true);

			// mix
			Assert::AreEqual((int_1 == float_1), false);

			// operator
			Token op_add(TokenType::ADD);
			Token op_add_2(TokenType::ADD);
			Token op_sub(TokenType::SUB);
			Assert::AreEqual((op_add == op_sub), false);
			Assert::AreEqual((op_add == op_add_2), true);

			// var_name
			Token var(TokenType::VAR, "var", 1.0f);
			Token var_2(TokenType::VAR, "var", 1.0f);
			Token num(TokenType::VAR, "num", 1.0f);
			Assert::AreEqual((var == var_2), true);
			Assert::AreEqual((var == num), false);

		}

		TEST_METHOD(Test_IsNumber)
		{
			Token token;

			Assert::IsTrue(IsNumber(Token(TokenType::INT, 1)),
				L"1 is number");
			Assert::IsTrue(IsNumber(Token(TokenType::FLOAT, 1.0f)),
				L"1.0f is number");
			Assert::IsTrue(IsNumber(Token(TokenType::FLOAT, 2.5f)),
				L"2.5f is number");
			Assert::IsFalse(IsNumber(Token(TokenType::VAR, "var", 1.0f)),
				L"var is not number");
			Assert::IsFalse(IsNumber(Token(TokenType::ADD)),
				L"+ is not number");
		}

		TEST_METHOD(Test_IsOperator)
		{
			Token token;

			Assert::IsTrue(IsOperator(Token(TokenType::ADD)),
				L"+ is operator");
			Assert::IsTrue(IsOperator(Token(TokenType::SUB)),
				L"- is operator");
			Assert::IsTrue(IsOperator(Token(TokenType::MUL)),
				L"* is operator");
			Assert::IsTrue(IsOperator(Token(TokenType::DIV)),
				L"/ is operator");
			Assert::IsFalse(IsOperator(Token(TokenType::INT, 1)),
				L"1 is not operator");
			Assert::IsFalse(IsOperator(Token(TokenType::FLOAT, 2.5f)),
				L"2.5 is not operator");

		}

		TEST_METHOD(Test_Class_AddCoefficient)
		{
			Token token(TokenType::VAR, "x", 1.0f);

			Assert::AreEqual(token.AddCoefficient(1.0f), 2.0f, L"1.0x -> 2.0x");
			Assert::AreEqual(token.AddCoefficient(1.0f), 3.0f, L"2.0x -> 3.0x");
		}
	};
}