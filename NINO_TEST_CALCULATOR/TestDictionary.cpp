#include "stdafx.h"
#include "CppUnitTest.h"
#include "Dictionary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using std::string;
using namespace calculator;

namespace NINO_TEST_CALCULATOR
{
	TEST_CLASS(TestDictionary)
	{
	public:

		TEST_METHOD(Test_AddToken)
		{
			Dictionary dict;
			SyntaxDict map;
			dict.AddToken(map, "+", Token(TokenType::ADD));

			bool result = (map.find("+")->second.GetType() == TokenType::ADD);
			Assert::AreEqual(result, true);
		}

		TEST_METHOD(Test_HasToken)
		{
			Dictionary dictionary = Dictionary();

			Assert::AreEqual(dictionary.HasToken("+"), true);
			Assert::AreEqual(dictionary.HasToken("-"), true);
			Assert::AreEqual(dictionary.HasToken("*"), true);
			Assert::AreEqual(dictionary.HasToken("/"), true);
			Assert::AreEqual(dictionary.HasToken("("), true);
			Assert::AreEqual(dictionary.HasToken(")"), true);
			Assert::AreEqual(dictionary.HasToken("int"), true);
			Assert::AreEqual(dictionary.HasToken("float"), true);
			Assert::AreEqual(dictionary.HasToken("="), true);

			Assert::AreEqual(dictionary.HasToken("?"), false);
			
		}

		TEST_METHOD(Test_FindToken)
		{
			Dictionary dictionary = Dictionary();
			bool result = false;

			result = (dictionary.FindToken("+").GetType() == TokenType::ADD);
			Assert::AreEqual(result, true);

			result = (dictionary.FindToken("?").GetType() == TokenType::ADD);
			Assert::AreEqual(result, false);

		}


	};
}