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
		TEST_METHOD(Test_OperatorEqual)
		{
			// int
			Token int_1(TokenType::INT, 1);
			Token int_2(TokenType::INT, 1);
			Token int_3(TokenType::INT, 2);

			Assert::AreEqual((int_1 == int_2), true);
			Assert::AreEqual((int_1 == int_3), false);

			// operator
			Token op_add(TokenType::ADD);
			Token op_add_2(TokenType::ADD);
			Token op_sub(TokenType::SUB);


			Assert::AreEqual((op_add == op_sub), false);
			Assert::AreEqual((op_add == op_add_2), true);
		}
	};
}