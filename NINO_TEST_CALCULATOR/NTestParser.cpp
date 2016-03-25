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
	TEST_CLASS(NTestParser)
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

		//���Խ��зָ�_�ӷ�
		TEST_METHOD(Test_NIsSplitBySymbol_CanSplit_Add)
		{
			vector<string> base = { "(", "1", "*", "2", ")", "+", "10" };

			bool correct = true;
			string n_operator = "+";
			auto iterSplit = base.begin();
			bool result = NIsSplitBySymbol(base, n_operator, iterSplit);

			Assert::AreEqual(result, correct);
		}

		//���ɽ��зָ�_����
		TEST_METHOD(Test_NIsSplitBySymbol_CanNotSplit_Sub)
		{
			vector<string> base = { "(", "1", "-", "5", ")", "*", "10" };

			bool correct = false;
			string n_operator = "-";
			auto iterSplit = base.begin();
			bool result = NIsSplitBySymbol(base, n_operator, iterSplit);

			Assert::AreEqual(result, correct);
		}

		//û�����ŵ������_�˷�
		TEST_METHOD(Test_NIsSplitBySymbol_HaveNotBracket_Mult)
		{
			vector<string> base = { "1", "+", "5", "+", "6" };

			bool correct = false;
			string n_operator = "*";
			auto iterSplit = base.begin();
			bool result = NIsSplitBySymbol(base, n_operator, iterSplit);

			Assert::AreEqual(result, correct);
		}

		//���ظ����ŵ������_����
		TEST_METHOD(Test_NIsSplitBySymbol_RepeatOperator_Div)
		{
			vector<string> base = { "(", "1", "/", "5", ")", "/", "6" };

			bool correct = true;
			string n_operator = "/";
			auto iterSplit = base.begin();
			bool result = NIsSplitBySymbol(base, n_operator, iterSplit);

			Assert::AreEqual(result, correct);
		}

		//�ó�iter��ԭ����iter�Ա�
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

		//Level-T:�������
		TEST_METHOD(Test_NEvaluateExpressionForT_SingleOperator)
		{
			vector<string> base = { "5", "*", "2" };

			float correct = 10.0f; 
			float result = NEvaluateExpressionForT(base);

			Assert::AreEqual(result, correct);
		}

		//Level-F:��������
		TEST_METHOD(Test_NEvaluateExpressionForF_LevelDescent)
		{
			vector<string> base = { "6" };

			float correct = 6.0f;
			float result = NEvaluateExpressionForF(base);

			Assert::AreEqual(result, correct);
		}

		//Level-F:���Ŵ���
		TEST_METHOD(Test_NEvaluateExpressionForF_Bracket)
		{
			vector<string> base = { "(", "6", "+", "1",")" };

			float correct = 7.0f;
			float result = NEvaluateExpressionForF(base);

			Assert::AreEqual(result, correct);
		}


		//Level-id:�ս��
		TEST_METHOD(Test_NEvaluateExpressionForId)
		{
			string base = "5";

			float correct = 5.0f;
			float result = NEvaluateExpressionForId(base);

			Assert::AreEqual(result, correct);
		}

		//�ӷ�
		TEST_METHOD(Test_NEvaluateExpression_Add)
		{
			vector<string> base = { "2", "+", "5" };

			float result = NEvaluateExpression(base);
			float correct = 7.0f;

			Assert::AreEqual(result, correct);
		}

		//�Ӽ���
		TEST_METHOD(Test_NEvaluateExpression_MixedAddAndSub)
		{
			vector<string> base = { "2", "+", "5", "-", "1" };

			float result = NEvaluateExpression(base);
			float correct = 6.0f;

			Assert::AreEqual(result, correct);
		}

		//��������
		TEST_METHOD(Test_NEvaluateExpression_Arithmetic)
		{
			vector<string> base = { "2", "+", "5", "-", "1" };

			float result = NEvaluateExpression(base);
			float correct = 6.0f;

			Assert::AreEqual(result, correct);
		}

		//������
		TEST_METHOD(Test_NEvaluateExpression_SingleBracket)
		{
			vector<string> base = { "(", "2", "+", "5", ")", "*", "7", "/", "7" };

			float result = NEvaluateExpression(base);
			float correct = 7.0f;

			Assert::AreEqual(result, correct);
		}

		//������
		TEST_METHOD(Test_NEvaluateExpression_MultipleBracket)
		{
			vector<string> base = { "(", "(", "2", "+", "5", ")", "*", "7", ")", "+", "5" };

			float result = NEvaluateExpression(base);
			float correct = 54.0f;

			Assert::AreEqual(result, correct);
		}
	};
}
