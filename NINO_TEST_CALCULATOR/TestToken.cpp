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
			Assert::AreEqual((token.GetType() == TokenType::ADD), true);
			Assert::AreEqual((token.GetIntValue() == 0), true);
			Assert::AreEqual((token.GetFloatValue() == 0.0f), true);

			// int
			token = Token(TokenType::INT, 5);
			Assert::AreEqual((token.GetType() == TokenType::INT), true);
			Assert::AreEqual((token.GetIntValue() == 5), true);
			Assert::AreEqual((token.GetFloatValue() == 0.0f), true);

			// float
			token = Token(TokenType::FLOAT, 6.0f);
			Assert::AreEqual((token.GetType() == TokenType::FLOAT), true);
			Assert::AreEqual((token.GetIntValue() == 0), true);
			Assert::AreEqual((token.GetFloatValue() == 6.0f), true);
			
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
		}
	};
}