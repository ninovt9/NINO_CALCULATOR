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
			Assert::AreEqual((ast.token_ == tokenList[3]), true);
			////Assert::AreEqual((ast.left_->left_->token_ == tokenList[0]), true);


		}



		//// for GetNodeTerm
		//tokenList = { Token(TokenType::INT, 5), Token(TokenType::MUL), Token(TokenType::INT, 1) };
		//ast = parser.GetNodeTerm(tokenList.begin(), tokenList.end());

		//Assert::AreEqual((ast.left_->token_ == tokenList[0]), true);
		//Assert::AreEqual((ast.token_ == tokenList[1]), true);
		//Assert::AreEqual((ast.right_->token_ == tokenList[2]), true);







		//TEST_METHOD(Test_CreateAst)
		//{
		//	Parser("1+5");
		//	int i = 0;
		//}



		//TEST_METHOD(Test_CreateAstNode_Number)
		//{
		//	Parser parser("5");
		//	auto iter = 
		//	AST ast;

		//	ast = parser.GetNodeFactor(make_shared< Token(TokenType::INT, 5));
		//	Assert::AreEqual(ast.token_.GetIntValue(), 5);
		//	ast = parser.GetNodeTerm(&Token(TokenType::INT, 5));
		//	Assert::AreEqual(ast.token_.GetIntValue(), 5);
		//	ast = parser.GetNodeExp(Token(TokenType::INT, 5));
		//	Assert::AreEqual(ast.token_.GetIntValue(), 5);
		//}

		//TEST_METHOD(Test_CreateAstNode_Add)
		//{
		//	Parser parser("5+1");
		//	AST ast;

		//	ast = parser.GetNodeFactor(Token(TokenType::INT, 5));
		//	Assert::AreEqual(ast.token_.GetIntValue(), 5)
		//}
	};
}