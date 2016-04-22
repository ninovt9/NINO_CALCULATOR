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

			Assert::AreEqual(scanner.GetNextChar(), '(');
			Assert::AreEqual(scanner.GetNextChar(), '1');
			Assert::AreEqual(scanner.GetNextChar(), '+');
			Assert::AreEqual(scanner.GetNextChar(), '2');
			Assert::AreEqual(scanner.GetNextChar(), ')');
			Assert::AreEqual(scanner.GetNextChar(), '*');
			Assert::AreEqual(scanner.GetNextChar(), '5');
		}
	};
}