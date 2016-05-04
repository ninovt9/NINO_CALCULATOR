#include "stdafx.h"
#include "CppUnitTest.h"
#include "NExpression.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using std::string;
using std::vector;
using std::invalid_argument;

namespace NINO_TEST_CALCULATOR
{
	TEST_CLASS(NTestExpression)
	{
	public:
		TEST_METHOD(Test_Calculate_HaveNotBracket)
		{
			string expression = "1+5+6";
			auto funcResult = NExpression::Calculate(expression);
			float correctResult = 12.0f;

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_Calculate_SingleBracket)
		{
			string expression = "(1+5)*6";
			auto funcResult = NExpression::Calculate(expression);
			float correctResult = 36.0f;

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_Calculate_MultipleBrackets)
		{
			string expression = "((1+5)*6)+1";
			auto funcResult = NExpression::Calculate(expression);
			float correctResult = 37.0f;

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_Calculate_WrongInputOfBracket)
		{
			string expression = "((1+5)*6(+";

			bool funcResult = false;
			bool correctResult = true;

			try {
				NExpression::Calculate(expression);
			}
			catch(invalid_argument err){
				funcResult = true;
			}
			

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_Calculate_WrongInputOfLetter)
		{
			string expression = "((1+5)*a";

			bool funcResult = false;
			bool correctResult = true;

			try {
				NExpression::Calculate(expression);
			}
			catch (invalid_argument err) {
				funcResult = true;
			}


			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_Calculate_WrongInputOfSingleOperator)
		{
			string expression = "+";

			bool funcResult = false;
			bool correctResult = true;

			try {
				NExpression::Calculate(expression);
			}
			catch (invalid_argument err) {
				funcResult = true;
			}


			Assert::AreEqual(funcResult, correctResult);
		}

		
	};
}