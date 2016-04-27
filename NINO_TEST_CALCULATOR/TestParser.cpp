#include "stdafx.h"
#include "CppUnitTest.h"
#include "Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using std::string;
using std::make_shared;
using namespace calculator;

namespace NINO_TEST_CALCULATOR
{
	TEST_CLASS(TestParser)
	{
	public:

		TEST_METHOD(Test_CreateAst)
		{
			Parser("1+5");
			int i = 0;
		}

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