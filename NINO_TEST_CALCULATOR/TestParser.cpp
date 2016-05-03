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

		TEST_METHOD(Test_GetNode_Number)
		{
			
			Parser parser = Parser();
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
			Parser parser = Parser();
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

		TEST_METHOD(Test_calculate)
		{
			Parser parser = Parser();
			std::shared_ptr<AST> node;
			vector<Token> tokenList;
			float result;

			// int
			node = make_shared<AST>(AST(Token(TokenType::INT, 5)));
			result = parser.calculate(node);
			Assert::AreEqual(result, 5.0f);

			// 5 * 1
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::MUL), Token(TokenType::INT, 1) };	// 5 * 1																						// for GetNodeTerm
			node = make_shared<AST>(parser.GetNodeTerm(tokenList.begin(), tokenList.end()));
			result = parser.calculate(node);
			Assert::AreEqual(result, 5.0f);
			
			// (7 + 2) / 5
			tokenList = { Token(TokenType::LEFT_PAR), Token(TokenType::INT, 7), Token(TokenType::ADD), Token(TokenType::INT, 2), Token(TokenType::RIGHT_PAR),
				Token(TokenType::DIV), Token(TokenType::INT, 5) };
			node = make_shared<AST>(parser.GetNodeExp(tokenList.begin(), tokenList.end()));
			result = parser.calculate(node);
			Assert::AreEqual(result, 1.8f);

			
		}
	};
}