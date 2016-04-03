#include "stdafx.h"
#include "CppUnitTest.h"
#include "NChecker.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using std::string;
using std::vector;
using std::invalid_argument;

namespace NINO_TEST_CALCULATOR
{
	TEST_CLASS(NTestChecker)
	{
	public:
		TEST_METHOD(Test_NCheckTokenError_ContainErrorOfLetter)
		{
			bool funcResult = false;
			bool correctResult = true;

			string expression = "a+1";
			try
			{
				NCheckTokenError(expression);
			}
			catch(invalid_argument err)
			{
				funcResult = true;
			}

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_NCheckTokenError_ContainErrorOfChinese)
		{
			bool funcResult = false;
			bool correctResult = true;

			string expression = "¸ò¸ò+1";
			try
			{
				NCheckTokenError(expression);
			}
			catch (invalid_argument err)
			{
				funcResult = true;
			}

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_NCheckTokenError_NotContainError)
		{
			bool funcResult = false;
			bool correctResult = false;

			string expression = "1+1";
			try
			{
				NCheckTokenError(expression);
			}
			catch (invalid_argument err)
			{
				funcResult = true;
			}

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_NCheckMatchError_NotMatch)
		{
			bool funcResult = false;
			bool correctResult = true;

			string expression = "(1+5";
			try
			{
				NCheckMatchError(expression);
			}
			catch (invalid_argument err)
			{
				funcResult = true;
			}

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_NCheckMatchError_NotMatchAndSameBracketNumber)
		{
			bool funcResult = false;
			bool correctResult = true;

			string expression = ")(1+5))";
			try
			{
				NCheckMatchError(expression);
			}
			catch (invalid_argument err)
			{
				funcResult = true;
			}

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_NCheckMatchError_Match)
		{
			bool funcResult = false;
			bool correctResult = false;

			string expression = "(1+5)";
			try
			{
				NCheckMatchError(expression);
			}
			catch (invalid_argument err)
			{
				funcResult = true;
			}

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_NCheckOperatorAdjacent)
		{
			bool funcResult = false;
			bool correctResult = true;

			string expression = "(1++5)";
			try
			{
				NCheckOperatorAdjacent(expression);
			}
			catch (invalid_argument err)
			{
				funcResult = true;
			}

			Assert::AreEqual(funcResult, correctResult);
		}
	};
}