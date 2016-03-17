#include "stdafx.h"
#include "CppUnitTest.h"
#include "NParser.h"
#include "NScanner.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <algorithm>

using std::string;
using std::vector;

namespace NINO_TEST_CALCULATOR
{
	TEST_CLASS(NTestNParser)
	{
	public:
		TEST_METHOD(Test_NIsInBracket_NotInBracket)
		{
			vector<string> base = {"(", "1", "*", "2", ")", "+", "10"};

			bool correct = false;
			bool result = NIsInBracket(base.begin(), base.begin() + 5);

			Assert::AreEqual(result, correct);
		}

		TEST_METHOD(Test_NIsInBracket_InBracket)
		{
			vector<string> base = { "(", "1", "+", "5", ")", "*", "10" };

			bool correct = true;
			bool result = NIsInBracket(base.begin(), base.begin() + 2);

			Assert::AreEqual(result, correct);
		}

		//可以进行分割_加法
		TEST_METHOD(Test_NIsSplitBySymbol_CanSplit_Add)
		{
			vector<string> base = { "(", "1", "*", "2", ")", "+", "10" };

			bool correct = true;
			string n_operator = "+";
			auto iterSplit = base.begin();
			bool result = NIsSplitBySymbol(base, n_operator, iterSplit);

			Assert::AreEqual(result, correct);
		}

		//不可进行分割_减法
		TEST_METHOD(Test_NIsSplitBySymbol_CanNotSplit_Sub)
		{
			vector<string> base = { "(", "1", "-", "5", ")", "*", "10" };

			bool correct = false;
			string n_operator = "-";
			auto iterSplit = base.begin();
			bool result = NIsSplitBySymbol(base, n_operator, iterSplit);

			Assert::AreEqual(result, correct);
		}

		//没有括号的情况下_乘法
		TEST_METHOD(Test_NIsSplitBySymbol_HaveNotBracket_Mult)
		{
			vector<string> base = { "1", "+", "5", "+", "6" };

			bool correct = false;
			string n_operator = "*";
			auto iterSplit = base.begin();
			bool result = NIsSplitBySymbol(base, n_operator, iterSplit);

			Assert::AreEqual(result, correct);
		}

		//有重复符号的情况下_除法
		TEST_METHOD(Test_NIsSplitBySymbol_RepeatOperator_Div)
		{
			vector<string> base = { "(", "1", "/", "5", ")", "/", "6" };

			bool correct = true;
			string n_operator = "/";
			auto iterSplit = base.begin();
			bool result = NIsSplitBySymbol(base, n_operator, iterSplit);

			Assert::AreEqual(result, correct);
		}
	};
}
