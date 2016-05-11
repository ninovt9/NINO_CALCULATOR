#include "stdafx.h"
#include "CppUnitTest.h"
#include "Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using std::string;
using std::vector;
using std::make_shared;
using namespace calculator;

namespace NINO_TEST_CALCULATOR
{
	TEST_CLASS(TestParser)
	{
	public:

		TEST_METHOD(Test_GetNode_Variable)
		{

			// error”√≤‚ ‘

			//Parser parser;
			//AST ast;
			//vector<Token> tokenList = { Token(TokenType::VAR, "var") };

			//ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			//Assert::AreEqual((ast.token_ == tokenList[0]), false);

			//Parser parser;
			//AST ast;
			//vector<Token> tokenList = { Token(TokenType::VAR, "var"), Token(TokenType::ASSIGNED) };

			//ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			//Assert::AreEqual((ast.token_ == tokenList[0]), false);

			Parser parser;
			AST ast;
			vector<Token> tokenList = { Token(TokenType::VAR, "var"), Token(TokenType::ASSIGNED), Token(TokenType::INT, 5)};

			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			Assert::AreEqual((ast.left_->token_ == tokenList[0]),		true,		L"var = 5 -> var");
			Assert::AreEqual((ast.token_ == tokenList[1]),				true,		L"var = 5 -> =");
			Assert::AreEqual((ast.right_->token_ == tokenList[2]),		true,		L"var = 5 -> 5");

		}

		TEST_METHOD(Test_GetNode_Number)
		{
			
			Parser parser;
			AST ast;
			vector<Token> tokenList = { Token(TokenType::INT, 5) };

			// for GetNodeFactor
			ast = parser.GetNodeFactor(tokenList.begin(), tokenList.end());
			Assert::AreEqual((ast.token_ == tokenList[0]), true);

			// for GetNodeTerm
			ast = parser.GetNodeTerm(tokenList.begin(), tokenList.end());
			Assert::AreEqual((ast.token_ == tokenList[0]), true);

			// for GetNodeExp
			ast = parser.GetNodeExp(tokenList.begin(), tokenList.end());
			Assert::AreEqual((ast.token_ == tokenList[0]), true);
		}

		TEST_METHOD(Test_GetNode_Expression)
		{
			Parser parser;
			AST ast;
			vector<Token> tokenList;

			// only mul
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::MUL), Token(TokenType::INT, 1) };	// 5 * 1

				// for GetNodeTerm
			ast = parser.GetNodeTerm(tokenList.begin(), tokenList.end());
			Assert::AreEqual((ast.left_->token_ == tokenList[0]), true);
			Assert::AreEqual((ast.token_ == tokenList[1]), true);
			Assert::AreEqual((ast.right_->token_ == tokenList[2]), true);

				// for GetNodeExp
			ast = parser.GetNodeExp(tokenList.begin(), tokenList.end());
			Assert::AreEqual((ast.left_->token_ == tokenList[0]), true);
			Assert::AreEqual((ast.token_ == tokenList[1]), true);
			Assert::AreEqual((ast.right_->token_ == tokenList[2]), true);

			// float
			tokenList = { Token(TokenType::FLOAT, 5.9), Token(TokenType::ADD), Token(TokenType::INT, 2) };

				// for GetNodeFactor
			ast = parser.GetNodeExp(tokenList.begin(), tokenList.end());
			Assert::AreEqual((ast.left_->token_ == tokenList[0]),	true,	L"float: 5.9 + 2 -> 5.9");
			Assert::AreEqual((ast.token_ == tokenList[1]),			true,	L"float: 5.9 + 2 -> +");
			Assert::AreEqual((ast.right_->token_ == tokenList[2]),	true,	L"float: 5.9 + 2 -> 2");

			// mix
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::MUL), Token(TokenType::INT, 1),
			Token(TokenType::ADD), Token(TokenType::INT, 2) };											// 5 * 1 + 2

				// for GetNodeExp
			ast = parser.GetNodeExp(tokenList.begin(), tokenList.end());
			Assert::AreEqual((ast.left_->left_->token_ == tokenList[0]), true);
			Assert::AreEqual((ast.left_->token_ == tokenList[1]), true);
			Assert::AreEqual((ast.left_->right_->token_ == tokenList[2]), true);
			Assert::AreEqual((ast.token_ == tokenList[3]), true);
			Assert::AreEqual((ast.right_->token_ == tokenList[4]), true);

			// contain par
			// (7 - 1)
			tokenList = { Token(TokenType::LEFT_PAR), Token(TokenType::INT, 7), Token(TokenType::SUB), Token(TokenType::INT, 1), Token(TokenType::RIGHT_PAR)};											
			
			ast = parser.GetNodeExp(tokenList.begin(), tokenList.end());
			Assert::AreEqual((ast.left_->token_ == tokenList[1]), true);
			Assert::AreEqual((ast.token_ == tokenList[2]), true);
			Assert::AreEqual((ast.right_->token_ == tokenList[3]), true);

			// (7 / 2)
			tokenList = { Token(TokenType::LEFT_PAR), Token(TokenType::INT, 7), Token(TokenType::DIV), Token(TokenType::INT, 2), Token(TokenType::RIGHT_PAR) };

			ast = parser.GetNodeTerm(tokenList.begin(), tokenList.end());
			Assert::AreEqual((ast.left_->token_ == tokenList[1]), true);
			Assert::AreEqual((ast.token_ == tokenList[2]), true);
			Assert::AreEqual((ast.right_->token_ == tokenList[3]), true);

			// (7 + 2) / 5
			tokenList = { Token(TokenType::LEFT_PAR), Token(TokenType::INT, 7), Token(TokenType::ADD), Token(TokenType::INT, 2), Token(TokenType::RIGHT_PAR),
			Token(TokenType::DIV), Token(TokenType::INT, 5)};

			ast = parser.GetNodeExp(tokenList.begin(), tokenList.end());
			Assert::AreEqual((ast.left_->left_->token_ == tokenList[1]), true);
			Assert::AreEqual((ast.left_->token_ == tokenList[2]), true);
			Assert::AreEqual((ast.left_->right_->token_ == tokenList[3]), true);
			Assert::AreEqual((ast.token_ == tokenList[5]), true);
			Assert::AreEqual((ast.right_->token_ == tokenList[6]), true);

		}
	};
}