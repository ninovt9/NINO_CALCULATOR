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
			Scanner scanner("var = 5.0");
			Parser parser(scanner.GetTokenList());
			auto ast = parser.GetAST();

			Assert::AreEqual((ast.token_ == Token(TokenType::ASSIGNMENT)),				true,		L"var = 5.0  ->  =");
			Assert::AreEqual((ast.left_->token_ == Token(TokenType::VAR, "var")),		true,		L"var = 5.0  ->  var");
			Assert::AreEqual((ast.right_->token_ == Token(TokenType::FLOAT, 5.0f)),		true,		L"var = 5.0  ->  50");


			// (5+1)
			scanner = Scanner("(5+1)");
			parser = Parser(scanner.GetTokenList());
			ast = parser.GetAST();

			Assert::AreEqual(parser.GetErrorReport().size(), static_cast<size_t>(0), L"(5+1) --> error=0");
		}

		TEST_METHOD(Test_GetNode_Variable)
		{

			Parser parser;
			AST ast;
			vector<Token> tokenList = { Token(TokenType::VAR, "var"), Token(TokenType::ASSIGNMENT), Token(TokenType::INT, 5)};

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
			tokenList = { Token(TokenType::VAR, "var"), Token(TokenType::ADD), Token(TokenType::INT, 1) };

			ast = parser.GetNodeExp(tokenList.begin(), tokenList.end());
			Assert::IsTrue(ast.left_->token_ == tokenList[0],		L"var + 1 -> var");
			Assert::IsTrue(ast.token_ == tokenList[1],				L"var + 1 -> +");
			Assert::IsTrue(ast.right_->token_ == tokenList[2],		L"var + 1 -> 1");

			// varA + varB
			tokenList = { Token(TokenType::VAR, "varA"), Token(TokenType::ADD), Token(TokenType::VAR, "varB") };

			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			Assert::IsTrue(ast.left_->token_ == tokenList[0],		L"varA + varB -> varA");
			Assert::IsTrue(ast.token_ == tokenList[1],				L"varA + varB -> +");
			Assert::IsTrue(ast.right_->token_ == tokenList[2],		L"varA + varB -> varB");
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
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax\n") != errorReport.end(), false, L"correct : 5");

			// 5+1 -> correct
			parser = Parser();
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::ADD), Token(TokenType::INT, 1) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax\n") != errorReport.end(), false, L"correct : 5+1");

			// 5*1 -> correct
			parser = Parser();
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::MUL), Token(TokenType::INT, 1) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax\n") != errorReport.end(), false, L"correct : 5*1");

			// a = 5 -> correct
			parser = Parser();
			tokenList = { Token(TokenType::VAR, "a"), Token(TokenType::ASSIGNMENT), Token(TokenType::INT, 5) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax\n") != errorReport.end(), false, L"correct : a=5");

			// 5++
			parser = Parser();
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::ADD), Token(TokenType::ADD) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax\n") != errorReport.end(), true, L"error : 5++");

			// 5+
			parser = Parser();
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::ADD)};
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax\n") != errorReport.end(), true, L"error : 5+");

			// 5 5
			parser = Parser();
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::INT, 5) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax\n") != errorReport.end(), true, L"error : 5 5");

			// 5+5 3
			parser = Parser();
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::ADD), Token(TokenType::INT, 5), Token(TokenType::INT, 3) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax\n") != errorReport.end(), true, L"error : 5+5 3");

			// 5+5*3 2
			parser = Parser();
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::ADD), Token(TokenType::INT, 5), Token(TokenType::MUL), Token(TokenType::INT, 3), Token(TokenType::INT, 2) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax\n") != errorReport.end(), true, L"error : 5+5*3 2");

			// (5+2
			parser = Parser();
			tokenList = { Token(TokenType::LEFT_PAR), Token(TokenType::INT, 5), Token(TokenType::ADD), Token(TokenType::INT, 5) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax\n") != errorReport.end(), true, L"error : (5+2");


			// var
			parser = Parser();
			tokenList = { Token(TokenType::VAR, "var") };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax\n") != errorReport.end(), true, L"error : var");

			// var = 
			parser = Parser();
			tokenList = { Token(TokenType::VAR, "var"), Token(TokenType::ASSIGNMENT) };
			ast = parser.GetNodeStat(tokenList.begin(), tokenList.end());
			errorReport = parser.GetErrorReport();
			Assert::AreEqual(std::find(errorReport.begin(), errorReport.end(), "SyntaxError: invalid syntax\n") != errorReport.end(), true, L"error : var =");
		}
	};
}