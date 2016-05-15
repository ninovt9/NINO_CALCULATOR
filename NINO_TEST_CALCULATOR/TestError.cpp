#include "stdafx.h"
#include "CppUnitTest.h"
#include "Error.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace calculator;

namespace NINO_TEST_CALCULATOR
{
	TEST_CLASS(TestDictionary)
	{
	public:

		TEST_METHOD(Test_ErrorToken)
		{
			std::string msg;
			std::string errorReport;

			msg = "scanner error";
			ErrorToken(msg, errorReport);
			Assert::AreEqual((errorReport=="TokenError: scanner error\n"), true);
		}

		TEST_METHOD(Test_ErrorSyntax)
		{
			std::string msg;
			std::string errorReport;

			msg = "scanner error";
			ErrorSyntax(msg, errorReport);
			Assert::AreEqual((errorReport=="SyntaxError: scanner error\n"), true);
		}
	};
}