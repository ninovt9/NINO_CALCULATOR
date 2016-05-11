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

			token = Token(TokenType::ASSIGNED);
			Assert::AreEqual((token.GetType() == TokenType::ASSIGNED),	true,		L"= -> type");
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


			// var_type
			token = Token(TokenType::TYPE_INT);
			Assert::AreEqual((token.GetType() == TokenType::TYPE_INT),	true,		L"int ->  type");
			Assert::AreEqual((token.GetIntValue() == 0),				true,		L"int ->  intValue");
			Assert::AreEqual((token.GetFloatValue() ==  0.0f),			true,		L"int ->  floatValue");
			Assert::AreEqual((token.GetVarName() == ""),				true,		L"int ->  text");

			// var
			token = Token(TokenType::VAR, "each");
			Assert::AreEqual((token.GetType() == TokenType::VAR),		true,		L"var:each ->  type");
			Assert::AreEqual((token.GetIntValue() == 0),				true,		L"var:each ->  intValue");
			Assert::AreEqual((token.GetFloatValue() == 0.0f),			true,		L"var:each ->  floatValue");
			Assert::AreEqual((token.GetVarName() == "each"),			true,		L"var:each ->  varName");

			
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

			// var_type
			Token type_int(TokenType::TYPE_INT);
			Token type_int_2(TokenType::TYPE_INT);
			Token type_float(TokenType::TYPE_FLOAT);
			Assert::AreEqual((type_int == type_int_2), true);
			Assert::AreEqual((type_int == type_float), false);

			// var_name
			Token var(TokenType::VAR, "var");
			Token var_2(TokenType::VAR, "var");
			Token num(TokenType::VAR, "num");
			Assert::AreEqual((var == var_2), true);
			Assert::AreEqual((var == num), false);

		}
	};
}