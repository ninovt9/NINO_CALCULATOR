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

		//得出iter与原容器iter对比
		TEST_METHOD(Test_NIsSplitBySymbol_MakeComparisonOfIter)
		{
			vector<string> base = { "1", "*", "5" };

			auto correct = base.begin() + 1;
			string n_operator = "*";
			auto resultIter = base.begin();
			NIsSplitBySymbol(base, n_operator, resultIter);

			bool isTrue = (resultIter == correct);
			Assert::AreEqual(isTrue, true);
		}

		//Level-T:单运算符
		TEST_METHOD(Test_NEvaluateExpressionForT_SingleOperator)
		{
			vector<string> base = { "5", "*", "2" };

			float correct = 10.0f; 
			float result = NEvaluateExpressionForT(base);

			Assert::AreEqual(result, correct);
		}

		//Level-F:降级测试
		TEST_METHOD(Test_NEvaluateExpressionForF_LevelDescent)
		{
			vector<string> base = { "6" };

			float correct = 6.0f;
			float result = NEvaluateExpressionForF(base);

			Assert::AreEqual(result, correct);
		}

		//Level-F:括号处理
		TEST_METHOD(Test_NEvaluateExpressionForF_Bracket)
		{
			vector<string> base = { "(", "6", "+", "1",")" };

			float correct = 7.0f;
			float result = NEvaluateExpressionForF(base);

			Assert::AreEqual(result, correct);
		}


		//Level-id:终结符
		TEST_METHOD(Test_NEvaluateExpressionForId)
		{
			string base = "5";

			float correct = 5.0f;
			float result = NEvaluateExpressionForId(base);

			Assert::AreEqual(result, correct);
		}

		//加法
		TEST_METHOD(Test_NEvaluateExpression_Add)
		{
			vector<string> base = { "2", "+", "5" };

			float result = NEvaluateExpression(base);
			float correct = 7.0f;

			Assert::AreEqual(result, correct);
		}

		//加减法
		TEST_METHOD(Test_NEvaluateExpression_MixedAddAndSub)
		{
			vector<string> base = { "2", "+", "5", "-", "1" };

			float result = NEvaluateExpression(base);
			float correct = 6.0f;

			Assert::AreEqual(result, correct);
		}

		//四则运算
		TEST_METHOD(Test_NEvaluateExpression_Arithmetic)
		{
			vector<string> base = { "2", "+", "5", "-", "1" };

			float result = NEvaluateExpression(base);
			float correct = 6.0f;

			Assert::AreEqual(result, correct);
		}

		//单括号
		TEST_METHOD(Test_NEvaluateExpression_SingleBracket)
		{
			vector<string> base = { "(", "2", "+", "5", ")", "*", "7", "/", "7" };

			float result = NEvaluateExpression(base);
			float correct = 7.0f;

			Assert::AreEqual(result, correct);
		}

		//多括号
		TEST_METHOD(Test_NEvaluateExpression_MultipleBracket)
		{
			vector<string> base = { "(", "(", "2", "+", "5", ")", "*", "7", ")", "+", "5" };

			float result = NEvaluateExpression(base);
			float correct = 54.0f;

			Assert::AreEqual(result, correct);
		}
	};
}
