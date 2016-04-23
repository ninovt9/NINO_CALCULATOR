#include "stdafx.h"
#include "CppUnitTest.h"
#include "Scanner.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace calculator;

namespace NINO_TEST_CALCULATOR
{
	TEST_CLASS(TestScanner)
	{
	public:
		TEST_METHOD(Test_InitExpression)
		{
			Scanner scanner("(1+2)*5");

			//因为在构造函数里掉用一次GetNextChar
			//Assert::AreEqual(scanner.GetNextChar(), '(');
			Assert::AreEqual(scanner.GetNextChar(), '1');
			Assert::AreEqual(scanner.GetNextChar(), '+');
			Assert::AreEqual(scanner.GetNextChar(), '2');
			Assert::AreEqual(scanner.GetNextChar(), ')');
			Assert::AreEqual(scanner.GetNextChar(), '*');
			Assert::AreEqual(scanner.GetNextChar(), '5');
		}

		TEST_METHOD(Test_GetNextToken)
		{
			Scanner scanner("(1+2)*5");
			bool result = false;

			result = (scanner.GetNextToken().GetType() == TokenType::LEFT_PAR);
			Assert::AreEqual(result, true);
			result = (scanner.GetNextToken().GetType() == TokenType::INT);
			Assert::AreEqual(result, true);
			result = (scanner.GetNextToken().GetType() == TokenType::ADD);
			Assert::AreEqual(result, true);
			result = (scanner.GetNextToken().GetType() == TokenType::INT);
			Assert::AreEqual(result, true);
			result = (scanner.GetNextToken().GetType() == TokenType::RIGHT_PAR);
			Assert::AreEqual(result, true);
			result = (scanner.GetNextToken().GetType() == TokenType::MUL);
			Assert::AreEqual(result, true);
			result = (scanner.GetNextToken().GetType() == TokenType::INT);
			Assert::AreEqual(result, true);
			result = (scanner.GetNextToken().GetType() == TokenType::INVALID);
			Assert::AreEqual(result, true);
		}
		
	};
}