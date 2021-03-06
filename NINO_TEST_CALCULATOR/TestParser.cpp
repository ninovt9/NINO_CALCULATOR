#include "stdafx.h"
#include "CppUnitTest.h"
#include "Parser.h"

#include <algorithm>

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

		TEST_METHOD(Test_Class_GetAST)
		{
			// var = 5.0
			auto ast = Parser(Scanner("var = 5.0").GetTokenList()).GetAST();

			Assert::AreEqual((ast.token_ == Token(TokenType::ASSIGNMENT)),				true,		L"var = 5.0  ->  =");
			Assert::AreEqual((ast.left_->token_ == Token(TokenType::VAR, "var", 1.0f)),		true,		L"var = 5.0  ->  var");
			Assert::AreEqual((ast.right_->token_ == Token(TokenType::FLOAT, 5.0f)),		true,		L"var = 5.0  ->  50");


			// (5+1)
			Parser parser(Scanner("(5+1)").GetTokenList());
			parser.GetAST();

			Assert::AreEqual(parser.GetErrorReport().size(), static_cast<size_t>(0), L"(5+1) --> error=0");
		}

		TEST_METHOD(Test_GetNode_Variable)
		{
			// var = 5
			auto ast = Parser(Scanner("var = 5").GetTokenList()).GetAST();

			Assert::IsTrue(ast.left_->token_	==	Token(TokenType::VAR, "var", 1.0f),		L"var = 5 -> var");
			Assert::IsTrue(ast.token_ 			==	Token(TokenType::ASSIGNMENT),		L"var = 5 -> =");
			Assert::IsTrue(ast.right_->token_	==	Token(TokenType::INT, 5),			L"var = 5 -> 5");

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

			// 5 + 1
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::MUL), Token(TokenType::INT, 1) };

			ast = parser.GetNodeTerm(tokenList.begin(), tokenList.end());
			Assert::AreEqual((ast.left_->token_ == tokenList[0]), true);
			Assert::AreEqual((ast.token_ == tokenList[1]), true);
			Assert::AreEqual((ast.right_->token_ == tokenList[2]), true);

			ast = parser.GetNodeExp(tokenList.begin(), tokenList.end());
			Assert::AreEqual((ast.left_->token_ == tokenList[0]), true);
			Assert::AreEqual((ast.token_ == tokenList[1]), true);
			Assert::AreEqual((ast.right_->token_ == tokenList[2]), true);

			// 5.9 + 2
			tokenList = { Token(TokenType::FLOAT, 5.9), Token(TokenType::ADD), Token(TokenType::INT, 2) };

			ast = parser.GetNodeExp(tokenList.begin(), tokenList.end());
			Assert::AreEqual((ast.left_->token_ == tokenList[0]),	true,	L"float: 5.9 + 2 -> 5.9");
			Assert::AreEqual((ast.token_ == tokenList[1]),			true,	L"float: 5.9 + 2 -> +");
			Assert::AreEqual((ast.right_->token_ == tokenList[2]),	true,	L"float: 5.9 + 2 -> 2");

			// 5 * 1 + 2
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::MUL), Token(TokenType::INT, 1),
			Token(TokenType::ADD), Token(TokenType::INT, 2) };											

			ast = parser.GetNodeExp(tokenList.begin(), tokenList.end());
			Assert::AreEqual((ast.left_->left_->token_ == tokenList[0]), true);
			Assert::AreEqual((ast.left_->token_ == tokenList[1]), true);
			Assert::AreEqual((ast.left_->right_->token_ == tokenList[2]), true);
			Assert::AreEqual((ast.token_ == tokenList[3]), true);
			Assert::AreEqual((ast.right_->token_ == tokenList[4]), true);

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

			// var + 1
			tokenList = { Token(TokenType::VAR, "var", 1.0f), Token(TokenType::ADD), Token(TokenType::INT, 1) };

			ast = parser.GetNodeExp(tokenList.begin(), tokenList.end());
			Assert::IsTrue(ast.left_->token_ == tokenList[0],		L"var + 1 -> var");
			Assert::IsTrue(ast.token_ == tokenList[1],				L"var + 1 -> +");
			Assert::IsTrue(ast.right_->token_ == tokenList[2],		L"var + 1 -> 1");

			// varA + varB
			tokenList = { Token(TokenType::VAR, "varA", 1.0f), Token(TokenType::ADD), Token(TokenType::VAR, "varB", 1.0f) };

			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			Assert::IsTrue(ast.left_->token_ == tokenList[0],		L"varA + varB -> varA");
			Assert::IsTrue(ast.token_ == tokenList[1],				L"varA + varB -> +");
			Assert::IsTrue(ast.right_->token_ == tokenList[2],		L"varA + varB -> varB");

			// x + 5 = 10
			tokenList = { Token(TokenType::VAR, "x", 1.0f), Token(TokenType::ADD), Token(TokenType::INT, 5),
			Token(TokenType::ASSIGNMENT), Token(TokenType::INT, 10) };

			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			Assert::IsTrue(ast.left_->left_->token_		== tokenList[0],		L"x + 5 = 10 -> x");
			Assert::IsTrue(ast.left_->token_			== tokenList[1],		L"x + 5 = 10 -> +");
			Assert::IsTrue(ast.left_->right_->token_	== tokenList[2],		L"x + 5 = 10 -> 5");
			Assert::IsTrue(ast.token_					== tokenList[3],		L"x + 5 = 10 -> =");
			Assert::IsTrue(ast.right_->token_			== tokenList[4],		L"x + 5 = 10 -> 10");


			// (0.0 + 5) for GetNodeFactor
			tokenList = Scanner("(0.0 + 5)").GetTokenList();
			ast = parser.GetNodeFactor(tokenList.begin(), tokenList.end());
			Assert::IsTrue(ast.token_			== Token(TokenType::ADD),			L"GetNodeFactor(0.0 + 5) -> +");
			Assert::IsTrue(ast.left_->token_	== Token(TokenType::FLOAT, 0.0f),	L"GetNodeFactor(0.0 + 5) -> 0.0");
			Assert::IsTrue(ast.right_->token_	== Token(TokenType::INT, 5),		L"GetNodeFactor(0.0 + 5) -> 5");


			// (0.0 + 5) for GetNodeTerm
			tokenList = Scanner("(0.0 + 5)").GetTokenList();
			ast = parser.GetNodeTerm(tokenList.begin(), tokenList.end());
			Assert::IsTrue(ast.token_			==	Token(TokenType::ADD),				L"GetNodeTerm(0.0 + 5) -> +");
			Assert::IsTrue(ast.left_->token_	==	Token(TokenType::FLOAT, 0.0f),		L"GetNodeTerm(0.0 + 5) -> 0.0");
			Assert::IsTrue(ast.right_->token_	==	Token(TokenType::INT, 5),			L"GetNodeTerm(0.0 + 5) -> 5");


			// ((0.0 + 5) * 3) for GetNodeFactor
			tokenList = Scanner("((0.0 + 5) * 3)").GetTokenList();
			ast = parser.GetNodeTerm(tokenList.begin(), tokenList.end());
			Assert::IsTrue(ast.token_					== Token(TokenType::MUL),				L"GetNodeFactor((0.0 + 5) * 3) -> *");
			Assert::IsTrue(ast.left_->token_			== Token(TokenType::ADD),				L"GetNodeFactor((0.0 + 5) * 3) -> +");
			Assert::IsTrue(ast.left_->left_->token_		== Token(TokenType::FLOAT, 0.0f),		L"GetNodeFactor((0.0 + 5) * 3) -> 0.0");
			Assert::IsTrue(ast.left_->right_->token_	== Token(TokenType::INT, 5),			L"GetNodeFactor((0.0 + 5) * 3) -> 5");
			Assert::IsTrue(ast.right_->token_			== Token(TokenType::INT, 3),			L"GetNodeFactor((0.0 + 5) * 3) -> 3");
			Assert::AreEqual(parser.GetErrorReport().size(),	static_cast<size_t>(0),					L"GetNodeFactor((0.0 + 5) * 3) -> errorReport");

			// 10 - (0.0 + 5)
			tokenList = Scanner("10-(0.0+5)").GetTokenList();
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			Assert::IsTrue(ast.token_					== Token(TokenType::SUB),			L"10 - (0.0 + 5) - > -");
			Assert::IsTrue(ast.left_->token_			== Token(TokenType::INT, 10),		L"10 - (0.0 + 5) - > 10");
			Assert::IsTrue(ast.right_->token_			== Token(TokenType::ADD),			L"10 - (0.0 + 5) - > +");
			Assert::IsTrue(ast.right_->left_->token_	== Token(TokenType::FLOAT, 0.0f),	L"10 - (0.0 + 5) - > 0.0");
			Assert::IsTrue(ast.right_->right_->token_	== Token(TokenType::INT, 5),		L"10 - (0.0 + 5) - > 5");

		}

		TEST_METHOD(Test_Class_Error)
		{
			Parser parser;
			AST ast;
			vector<Token> tokenList;
			vector<string> errorReport;

			// 5 -> correct
			parser = Parser();
			tokenList = { Token(TokenType::INT, 5)};
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax") != errorReport.end(), false, L"correct : 5");

			// 5+1 -> correct
			parser = Parser();
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::ADD), Token(TokenType::INT, 1) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax") != errorReport.end(), false, L"correct : 5+1");

			// 5*1 -> correct
			parser = Parser();
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::MUL), Token(TokenType::INT, 1) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax") != errorReport.end(), false, L"correct : 5*1");

			// a = 5 -> correct
			parser = Parser();
			tokenList = { Token(TokenType::VAR, "a", 1.0f), Token(TokenType::ASSIGNMENT), Token(TokenType::INT, 5) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax") != errorReport.end(), false, L"correct : a=5");


			// 5++
			parser = Parser();
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::ADD), Token(TokenType::ADD) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax") != errorReport.end(), true, L"error : 5++");

			// 5+
			parser = Parser();
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::ADD)};
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax") != errorReport.end(), true, L"error : 5+");

			// 5 5
			parser = Parser();
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::INT, 5) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax") != errorReport.end(), true, L"error : 5 5");

			// 5+5 3
			parser = Parser();
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::ADD), Token(TokenType::INT, 5), Token(TokenType::INT, 3) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax") != errorReport.end(), true, L"error : 5+5 3");

			// 5+5*3 2
			parser = Parser();
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::ADD), Token(TokenType::INT, 5), Token(TokenType::MUL), Token(TokenType::INT, 3), Token(TokenType::INT, 2) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax") != errorReport.end(), true, L"error : 5+5*3 2");

			// (5+2
			parser = Parser();
			tokenList = { Token(TokenType::LEFT_PAR), Token(TokenType::INT, 5), Token(TokenType::ADD), Token(TokenType::INT, 5) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax") != errorReport.end(), true, L"error : (5+2");

			//// var
			//parser = Parser();
			//tokenList = { Token(TokenType::VAR, "var") };
			//ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			//errorReport = parser.GetErrorReport();
			//Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax") != errorReport.end(), true, L"error : var");

			// var = 
			parser = Parser();
			tokenList = { Token(TokenType::VAR, "var", 1.0f), Token(TokenType::ASSIGNMENT) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax") != errorReport.end(), true, L"error : var =");
		}
	};
}