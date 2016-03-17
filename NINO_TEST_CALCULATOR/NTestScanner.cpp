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

		TEST_METHOD(Test_REGEX_MULT_NUMBER_integer)
		{
			string base = "123";
			smatch result;
			auto isTrue = regex_match(base, result, MULT_NUMBER_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_MULT_NUMBER_integer_false)
		{
			string base = "023";
			smatch result;
			auto isTrue = regex_match(base, result, MULT_NUMBER_REGEX);

			Assert::AreEqual(isTrue, false);
		}

		TEST_METHOD(Test_REGEX_MULT_NUMBER_zero)
		{
			string base = "0";
			smatch result;
			auto isTrue = regex_match(base, result, MULT_NUMBER_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_MULT_NUMBER_zero_false)
		{
			string base = "000";
			smatch result;
			auto isTrue = regex_match(base, result, MULT_NUMBER_REGEX);

			Assert::AreEqual(isTrue, false);
		}

		TEST_METHOD(Test_REGEX_MULT_NUMBER_decimal)
		{
			string base = "0.5";
			smatch result;
			auto isTrue = regex_match(base, result, MULT_NUMBER_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_SINGLE_NUMBER)
		{
			string base = "5";
			smatch result;
			auto isTrue = regex_match(base, result, SINGLE_NUMBER_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_SINGLE_NUMBER_zero)
		{
			string base = "0";
			smatch result;
			auto isTrue = regex_match(base, result, SINGLE_NUMBER_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_SINGLE_NUMBER_point)
		{
			string base = ".";
			smatch result;
			auto isTrue = regex_match(base, result, SINGLE_NUMBER_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_SPACE_1)
		{
			string base = " ";
			smatch result;
			auto isTrue = regex_match(base, result, SPACE_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_SPACE_more)
		{ 
			string base = "        ";
			smatch result;
			auto isTrue = regex_match(base, result, SPACE_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_SPACE_false)
		{
			string base = "   +";
			smatch result;
			auto isTrue = regex_match(base, result, SPACE_REGEX);

			Assert::AreEqual(isTrue, false);
		}

		TEST_METHOD(Test_REGEX_ADD)
		{
			string base = "+";
			smatch result;
			auto isTrue = regex_match(base, result, ADD_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_ADD_false)
		{
			string base = "-";
			smatch result;
			auto isTrue = regex_match(base, result, ADD_REGEX);

			Assert::AreEqual(isTrue, false);
		}

		TEST_METHOD(Test_REGEX_SUB)
		{
			string base = "-";
			smatch result;
			auto isTrue = regex_match(base, result, SUB_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_SUB_false)
		{
			string base = "*";
			smatch result;
			auto isTrue = regex_match(base, result, SUB_REGEX);

			Assert::AreEqual(isTrue, false);
		}

		TEST_METHOD(Test_REGEX_MUL)
		{
			string base = "*";
			smatch result;
			auto isTrue = regex_match(base, result, MUL_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_MUL_false)
		{
			string base = "-";
			smatch result;
			auto isTrue = regex_match(base, result, MUL_REGEX);

			Assert::AreEqual(isTrue, false);
		}

		TEST_METHOD(Test_REGEX_DIV)
		{
			string base = "/";
			smatch result;
			auto isTrue = regex_match(base, result, DIV_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_DIV_false)
		{
			string base = "+";
			smatch result;
			auto isTrue = regex_match(base, result, DIV_REGEX);

			Assert::AreEqual(isTrue, false);
		}

		TEST_METHOD(Test_REGEX_OPERATOR_ADD)
		{
			string base = "+";
			smatch result;
			auto isTrue = regex_match(base, result, OPERATOR_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_OPERATOR_SUB)
		{
			string base = "-";
			smatch result;
			auto isTrue = regex_match(base, result, OPERATOR_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_OPERATOR_MUL)
		{
			string base = "*";
			smatch result;
			auto isTrue = regex_match(base, result, OPERATOR_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_OPERATOR_DIV)
		{
			string base = "/";
			smatch result;
			auto isTrue = regex_match(base, result, OPERATOR_REGEX);

			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_REGEX_OPERATOR_false)
		{
			string base = "=";
			smatch result;
			auto isTrue = regex_match(base, result, OPERATOR_REGEX);

			Assert::AreEqual(isTrue, false);
		}

		TEST_METHOD(Test_NGetTokenList)
		{
			//带空格
			string base = "1-2/3";
			vector<string> correct = { "1", "-", "2", "/", "3" };
			auto result = NGetTokenList(base);

			bool isTrue = equal(result.begin(), result.end(), correct.begin(), correct.end());
			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_NGetTokenList_space_1)
		{
			//带空格
			string base = "1 + 2 + 3";
			vector<string> correct = { "1", "+", "2", "+", "3" };
			auto result = NGetTokenList(base);

			bool isTrue = equal(result.begin(), result.end(), correct.begin(), correct.end());
			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_NGetTokenList_space_2)
		{
			//带空格
			string base = "1 -2 + 3";
			vector<string> correct = { "1", "-", "2", "+", "3" };
			auto result = NGetTokenList(base);

			bool isTrue = equal(result.begin(), result.end(), correct.begin(), correct.end());
			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_NGetTokenList_space_zero)
		{
			//带空格
			string base = "1 -0 + 3";
			vector<string> correct = { "1", "-", "0", "+", "3" };
			auto result = NGetTokenList(base);

			bool isTrue = equal(result.begin(), result.end(), correct.begin(), correct.end());
			Assert::AreEqual(isTrue, true);
		}

		TEST_METHOD(Test_NGetTokenList_space_decimal)
		{
			//带空格
			string base = "1.7 -0.5 + 3";
			vector<string> correct = { "1.7", "-", "0.5", "+", "3" };
			auto result = NGetTokenList(base);

			bool isTrue = equal(result.begin(), result.end(), correct.begin(), correct.end());
			Assert::AreEqual(isTrue, true);
		}
	};
}