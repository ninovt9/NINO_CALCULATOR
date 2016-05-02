#include "stdafx.h"
#include "CppUnitTest.h"
#include "Scanner.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace calculator;

using std::string;
using std::stringstream;
using std::vector;

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

			// contain space
			stream = stringstream("1 +5");
			Assert::AreEqual(scanner.GetNextChar(stream), '1');
			Assert::AreEqual(scanner.GetNextChar(stream), '+');
			Assert::AreEqual(scanner.GetNextChar(stream), '5');

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

			// more
			stream = stringstream("659");
			currectChar = stream.get();
			token = scanner.HandleNumberState(stream, currectChar);

			Assert::AreEqual((token.GetType() == TokenType::INT), true);
			Assert::AreEqual(token.GetIntValue(), 659);

			//¿Õ¸ñ
		}

		TEST_METHOD(Test_GetNextToken)
		{
			Scanner scanner = Scanner();

			stringstream stream;
			Token token;

			
			// add
			stream = stringstream("75+9");

			token = scanner.GetNextToken(stream);
			Assert::AreEqual((token.GetType() == TokenType::INT), true);
			Assert::AreEqual(token.GetIntValue(), 75);

			token = scanner.GetNextToken(stream);
			Assert::AreEqual((token.GetType() == TokenType::ADD), true);

			token = scanner.GetNextToken(stream);
			Assert::AreEqual((token.GetType() == TokenType::INT), true);
			Assert::AreEqual(token.GetIntValue(), 9);

			token = scanner.GetNextToken(stream);
			Assert::AreEqual((token.GetType() == TokenType::INVALID), true);

			// space
			stream = stringstream(" 75 + 9 ");

			token = scanner.GetNextToken(stream);
			Assert::AreEqual((token.GetType() == TokenType::INT), true);
			Assert::AreEqual(token.GetIntValue(), 75);

			token = scanner.GetNextToken(stream);
			Assert::AreEqual((token.GetType() == TokenType::ADD), true);

			token = scanner.GetNextToken(stream);
			Assert::AreEqual((token.GetType() == TokenType::INT), true);
			Assert::AreEqual(token.GetIntValue(), 9);

			token = scanner.GetNextToken(stream);
			Assert::AreEqual((token.GetType() == TokenType::INVALID), true);
		}

		TEST_METHOD(Test_GetTokenList)
		{
			Scanner scanner = Scanner();

			stringstream stream;
			vector<Token> tokenList;



			stream = stringstream("1/5*6");
			tokenList = scanner.GetTokenList(stream);

			Assert::AreEqual((tokenList[0].GetType() == TokenType::INT), true);
			Assert::AreEqual(tokenList[0].GetIntValue(), 1);

			Assert::AreEqual((tokenList[1].GetType() == TokenType::DIV), true);

			Assert::AreEqual((tokenList[2].GetType() == TokenType::INT), true);
			Assert::AreEqual(tokenList[2].GetIntValue(), 5);

			Assert::AreEqual((tokenList[3].GetType() == TokenType::MUL), true);

			Assert::AreEqual((tokenList[4].GetType() == TokenType::INT), true);
			Assert::AreEqual(tokenList[4].GetIntValue(), 6);



			// contain space
			stream = stringstream(" 1 / 5 * 6 ");
			tokenList = scanner.GetTokenList(stream);

			Assert::AreEqual((tokenList[0].GetType() == TokenType::INT), true);
			Assert::AreEqual(tokenList[0].GetIntValue(), 1);

			Assert::AreEqual((tokenList[1].GetType() == TokenType::DIV), true);

			Assert::AreEqual((tokenList[2].GetType() == TokenType::INT), true);
			Assert::AreEqual(tokenList[2].GetIntValue(), 5);

			Assert::AreEqual((tokenList[3].GetType() == TokenType::MUL), true);

			Assert::AreEqual((tokenList[4].GetType() == TokenType::INT), true);
			Assert::AreEqual(tokenList[4].GetIntValue(), 6);



			// mult line
			stream = stringstream("1+5\n3");
				//first line
			tokenList = scanner.GetTokenList(stream);

			Assert::AreEqual((tokenList[0].GetType() == TokenType::INT), true);
			Assert::AreEqual(tokenList[0].GetIntValue(), 1);

			Assert::AreEqual((tokenList[1].GetType() == TokenType::ADD), true);

			Assert::AreEqual((tokenList[2].GetType() == TokenType::INT), true);
			Assert::AreEqual(tokenList[2].GetIntValue(), 5);

				//second line
			tokenList = scanner.GetTokenList(stream);

			Assert::AreEqual((tokenList[0].GetType() == TokenType::INT), true);
			Assert::AreEqual(tokenList[0].GetIntValue(), 3);

		}

	};
}