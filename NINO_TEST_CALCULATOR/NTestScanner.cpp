#include "stdafx.h"
#include "CppUnitTest.h"
#include "NScanner.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <algorithm>

using std::equal;
using std::string;
using std::regex_match;
using std::smatch;
using std::vector;

namespace NINO_TEST_CALCULATOR
{
	TEST_CLASS(NTestScanner)
	{
	public:

		TEST_METHOD(Test_MULT_NUMBER_REGEX_RightInputOfInteger)
		{
			string input = "123";
			smatch result;

			bool funcResult = regex_match(input, result, MULT_NUMBER_REGEX);
			bool correctResult = true;

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_REGEX_MULT_NUMBER_WrongInputOfInteger)
		{
			string input = "023";
			smatch result;
			auto isTrue = regex_match(input, result, MULT_NUMBER_REGEX);

			Assert::AreEqual(isTrue, false);
		}

		TEST_METHOD(Test_REGEX_MULT_NUMBER_RightInputOfZero)
		{
			string input = "0";
			smatch result;
			auto isTrue = regex_match(input, result, MULT_NUMBER_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_MULT_NUMBER_WrongInputOfZero)
		{
			string input = "000";
			smatch result;
			auto isTrue = regex_match(input, result, MULT_NUMBER_REGEX);

			Assert::AreEqual(isTrue, false);
		}

		TEST_METHOD(Test_REGEX_MULT_NUMBER_RightInputOfDecimal)
		{
			string input = "0.5";
			smatch result;
			auto isTrue = regex_match(input, result, MULT_NUMBER_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_MULT_NUMBER_RightInputOfDecimal_NoNumberAfterRadixPoint)
		{
			//小数点后没有数字，为了最长匹配用。。。
			string input = "1.";
			smatch result;
			auto isTrue = regex_match(input, result, MULT_NUMBER_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_SINGLE_NUMBER_RightInputOfInteger)
		{
			string input = "5";
			smatch result;
			auto isTrue = regex_match(input, result, SINGLE_NUMBER_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_SINGLE_NUMBER_RightInputOfZero)
		{
			string input = "0";
			smatch result;
			auto isTrue = regex_match(input, result, SINGLE_NUMBER_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_SINGLE_NUMBER_RightInputOfRadixPoint)
		{
			string input = ".";
			smatch result;
			auto isTrue = regex_match(input, result, SINGLE_NUMBER_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_SPACE_RightInputOfSingleSpace)
		{
			string input = " ";
			smatch result;
			auto isTrue = regex_match(input, result, SPACE_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_SPACE_RightInputOfMoreSpace)
		{ 
			string input = "        ";
			smatch result;
			auto isTrue = regex_match(input, result, SPACE_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_SPACE_WrongInput)
		{
			string input = "   +";
			smatch result;
			auto isTrue = regex_match(input, result, SPACE_REGEX);

			Assert::AreEqual(isTrue, false);
		}

		TEST_METHOD(Test_REGEX_OPERATOR_RightInputOfAdd)
		{
			string input = "+";
			smatch result;
			auto isTrue = regex_match(input, result, OPERATOR_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_OPERATOR_RightInputOfSub)
		{
			string input = "-";
			smatch result;
			auto isTrue = regex_match(input, result, OPERATOR_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_OPERATOR_RightInputOfMult)
		{
			string input = "*";
			smatch result;
			auto isTrue = regex_match(input, result, OPERATOR_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_OPERATOR_RightInputOfDiv)
		{
			string input = "/";
			smatch result;
			auto isTrue = regex_match(input, result, OPERATOR_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_OPERATOR_WrongInput)
		{
			string input = "=";
			smatch result;
			auto isTrue = regex_match(input, result, OPERATOR_REGEX);

			Assert::AreEqual(isTrue, false);
		}

		TEST_METHOD(Test_BRAKET_REGEX_RightInputOfLeftBraket)
		{
			string input = "(";
			smatch result;
			auto isTrue = regex_match(input, result, BRAKET_REGEX);

			Assert::AreEqual(isTrue, true);
		}


		TEST_METHOD(Test_BRAKET_REGEX_RightInputOfRightBraket)
		{
			string input = ")";
			smatch result;
			auto isTrue = regex_match(input, result, BRAKET_REGEX);

			Assert::AreEqual(isTrue, true);
		}


		TEST_METHOD(Test_BRAKET_REGEX_WrongInputOfNumber)
		{
			string input = "5";
			smatch result;
			auto isTrue = regex_match(input, result, BRAKET_REGEX);

			Assert::AreEqual(isTrue, false);
		}

		TEST_METHOD(Test_NIsTokenMatchRegex_RightInputOfNumber)
		{
			string token = "1";
			
			bool funcResult = NIsTokenMatchRegex(token);
			bool correctResult = true;

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_NIsTokenMatchRegex_RightInputOfDecimal)
		{
			string token = "2.5";

			bool funcResult = NIsTokenMatchRegex(token);
			bool correctResult = true;

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_NIsTokenMatchRegex_RightInputOfOperator)
		{
			string token = "+";

			bool funcResult = NIsTokenMatchRegex(token);
			bool correctResult = true;

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_NIsTokenMatchRegex_RightInputOfBracket)
		{
			string token = "(";

			bool funcResult = NIsTokenMatchRegex(token);
			bool correctResult = true;

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_NIsTokenMatchRegex_WrongInput)
		{
			string token = "(1+2)";

			bool funcResult = NIsTokenMatchRegex(token);
			bool correctResult = false;

			Assert::AreEqual(funcResult, correctResult);
		}

		TEST_METHOD(Test_NGetTokenList_RightInputOfTwoOperator)
		{
			//带空格
			string input = "1-2/3";
			vector<string> correct = { "1", "-", "2", "/", "3" };
			auto result = NGetTokenList(input);

			bool isTrue = equal(result.begin(), result.end(), correct.begin(), correct.end());
			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_NGetTokenList_RightInputOfContainSpace)
		{
			//带空格
			string input = "1 + 2 + 3";
			vector<string> correct = { "1", "+", "2", "+", "3" };
			auto result = NGetTokenList(input);

			bool isTrue = equal(result.begin(), result.end(), correct.begin(), correct.end());
			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_NGetTokenList_RightInputOfContainSpaceAndDifferentOperator)
		{
			//带空格
			string input = "1 -2 + 3";
			vector<string> correct = { "1", "-", "2", "+", "3" };
			auto result = NGetTokenList(input);

			bool isTrue = equal(result.begin(), result.end(), correct.begin(), correct.end());
			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_NGetTokenList_RightInputOfContainSpaceAndZero)
		{
			//带空格
			string input = "1 -0 + 3";
			vector<string> correct = { "1", "-", "0", "+", "3" };
			auto result = NGetTokenList(input);

			bool isTrue = equal(result.begin(), result.end(), correct.begin(), correct.end());
			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_NGetTokenList_RightInputOfContainSpaceAndDecimal)
		{
			//带空格
			string input = "1.7 -0.5 + 3";
			vector<string> correct = { "1.7", "-", "0.5", "+", "3" };
			auto result = NGetTokenList(input);

			bool isTrue = equal(result.begin(), result.end(), correct.begin(), correct.end());
			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_NGetTokenList_RightInputOfNestedBracket)
		{
			//带空格
			string input = "(1 + (5*3))";
			vector<string> correct = { "(", "1", "+", "(", "5", "*", "3", ")", ")"};
			auto result = NGetTokenList(input);

			bool isTrue = equal(result.begin(), result.end(), correct.begin(), correct.end());
			Assert::AreEqual(isTrue, true);
		}
	};
}