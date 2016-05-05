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
			Scanner scanner;
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
			Scanner scanner;
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
			Scanner scanner;

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

			//ø’∏Ò
		}

		TEST_METHOD(Test_GetNextToken)
		{
			Scanner scanner;

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

		TEST_METHOD(Test_GetNextTokenList)
		{
			Scanner scanner;

			stringstream stream;
			vector<Token> tokenList;



			stream = stringstream("1/5*6");
			tokenList = scanner.GetNextTokenList(stream);

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
			tokenList = scanner.GetNextTokenList(stream);

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
			tokenList = scanner.GetNextTokenList(stream);

			Assert::AreEqual((tokenList[0].GetType() == TokenType::INT), true);
			Assert::AreEqual(tokenList[0].GetIntValue(), 1);

			Assert::AreEqual((tokenList[1].GetType() == TokenType::ADD), true);

			Assert::AreEqual((tokenList[2].GetType() == TokenType::INT), true);
			Assert::AreEqual(tokenList[2].GetIntValue(), 5);

				//second line
			tokenList = scanner.GetNextTokenList(stream);

			Assert::AreEqual((tokenList[0].GetType() == TokenType::INT), true);
			Assert::AreEqual(tokenList[0].GetIntValue(), 3);

		}


		/*-------------------------------Class µœ÷-----------------------------*/

		TEST_METHOD(Test_Class_GetTokenList)
		{
			Scanner scanner;
			vector<Token> tokenList;

			// 1-2
			scanner = Scanner("1-2");
			tokenList = scanner.GetTokenList();

			Assert::AreEqual((tokenList[0] == Token(TokenType::INT, 1)), true);
			Assert::AreEqual((tokenList[1] == Token(TokenType::SUB)), true);
			Assert::AreEqual((tokenList[2] == Token(TokenType::INT, 2)), true);
			
		}

	};
}