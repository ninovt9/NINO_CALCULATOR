#include "stdafx.h"
#include "CppUnitTest.h"
#include "Scanner.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace calculator;

using std::string;
using std::stringstream;

namespace NINO_TEST_CALCULATOR
{
	TEST_CLASS(TestScanner)
	{
	public:
		TEST_METHOD(Test_GetNextChar)
		{
			Scanner scanner = Scanner();
			stringstream stream("1+5");

			Assert::AreEqual(scanner.GetNextChar(stream), '1');
			Assert::AreEqual(scanner.GetNextChar(stream), '+');
			Assert::AreEqual(scanner.GetNextChar(stream), '5');
			
			//out of stream
			char err = scanner.GetNextChar(stream);
			Assert::AreEqual(isdigit(err), 0);				//not a digit

		}

		TEST_METHOD(Test_HandleOperatorState)
		{
			Scanner scanner = Scanner();
			stringstream stream;
			char currectChar;
			Token token;

			// add
			stream = stringstream("+5");
			currectChar = stream.get();
			token = scanner.HandleOperatorState(stream, currectChar);

			Assert::AreEqual((token.GetType() == TokenType::ADD), true);

			// par
			stream = stringstream("(");
			currectChar = stream.get();
			token = scanner.HandleOperatorState(stream, currectChar);

			Assert::AreEqual((token.GetType() == TokenType::LEFT_PAR), true);
		}

		TEST_METHOD(Test_HandleNumberState)
		{
			Scanner scanner = Scanner();

			stringstream stream;
			char currectChar;
			Token token;

			// int
			stream = stringstream("6+1");
			currectChar = stream.get();
			token = scanner.HandleNumberState(stream, currectChar);

			Assert::AreEqual((token.GetType() == TokenType::INT), true);
			Assert::AreEqual(token.GetIntValue(), 6);

			stream = stringstream("659");
			currectChar = stream.get();
			token = scanner.HandleNumberState(stream, currectChar);

			Assert::AreEqual((token.GetType() == TokenType::INT), true);
			Assert::AreEqual(token.GetIntValue(), 659);
		}


		//TEST_METHOD(Test_InitExpression)
		//{
		//	Scanner scanner("(1+2)*5");

		//	//因为在构造函数里掉用一次GetNextChar
		//	//Assert::AreEqual(scanner.GetNextChar(), '(');
		//	Assert::AreEqual(scanner.GetNextChar(), '1');
		//	Assert::AreEqual(scanner.GetNextChar(), '+');
		//	Assert::AreEqual(scanner.GetNextChar(), '2');
		//	Assert::AreEqual(scanner.GetNextChar(), ')');
		//	Assert::AreEqual(scanner.GetNextChar(), '*');
		//	Assert::AreEqual(scanner.GetNextChar(), '5');
		//}

		TEST_METHOD(Test_GetNextToken_tokenType)
		{
			Scanner scanner("(1+2)*5");
			bool result = false;

			result = (scanner.GetNextToken().GetType() == TokenType::LEFT_PAR);
			Assert::AreEqual(result, true);
			result = (scanner.GetNextToken().GetType() == TokenType::INT);
			Assert::AreEqual(result, true);
			result = (scanner.GetNextToken().GetType() == TokenType::ADD);
			Assert::AreEqual(result, true);
			result = (scanner.GetNextToken().GetType() == TokenType::INT);
			Assert::AreEqual(result, true);
			result = (scanner.GetNextToken().GetType() == TokenType::RIGHT_PAR);
			Assert::AreEqual(result, true);
			result = (scanner.GetNextToken().GetType() == TokenType::MUL);
			Assert::AreEqual(result, true);
			result = (scanner.GetNextToken().GetType() == TokenType::INT);
			Assert::AreEqual(result, true);
			result = (scanner.GetNextToken().GetType() == TokenType::INVALID);
			Assert::AreEqual(result, true);



			

			//空格~暂时不写
		}

		TEST_METHOD(Test_GetNextToken_intValue)
		{
			//int value
			Scanner scanner("1+5");

			Assert::AreEqual(scanner.GetNextToken().GetIntValue(), 1);
			scanner.GetNextToken();
			Assert::AreEqual(scanner.GetNextToken().GetIntValue(), 5);
		}
		
		TEST_METHOD(Test_GetTokenList)
		{
			Scanner scanner("1+6");
			auto tokenList = scanner.GetTokenList();

			Assert::AreEqual(tokenList[0].GetIntValue(), 1);
			Assert::AreEqual(tokenList[2].GetIntValue(), 6);
		}
	};
}