#include "stdafx.h"
#include "CppUnitTest.h"
#include "Calculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using std::vector;
using std::string;
using std::map;
using std::make_shared;
using namespace calculator;

namespace NINO_TEST_CALCULATOR
{
	TEST_CLASS(TestCalculator)
	{
		TEST_METHOD(Test_Calculate)
		{
			Calculator cal;
			Parser	parser;
			float result;

			std::map<std::string, float> varList;
			std::vector<Token> tokenList;
			std::shared_ptr<AST> node;
		

			// int
			node = make_shared<AST>(AST(Token(TokenType::INT, 5)));
			result = cal.Calculate(node, varList);
			Assert::AreEqual(result, 5.0f);

			// 5 * 1
			tokenList = { Token(TokenType::INT, 5), Token(TokenType::MUL), Token(TokenType::INT, 1) };	// 5 * 1																						// for GetNodeTerm
			node = make_shared<AST>(parser.GetNodeTerm(tokenList.begin(), tokenList.end()));
			result = cal.Calculate(node, varList);
			Assert::AreEqual(result, 5.0f);

			// (7 + 2) / 5
			tokenList = { Token(TokenType::LEFT_PAR), Token(TokenType::INT, 7), Token(TokenType::ADD), Token(TokenType::INT, 2), Token(TokenType::RIGHT_PAR),
				Token(TokenType::DIV), Token(TokenType::INT, 5) };
			node = make_shared<AST>(parser.GetNodeExp(tokenList.begin(), tokenList.end()));
			result = cal.Calculate(node, varList);
			Assert::AreEqual(result, 1.8f);

			// 5.1 + 3.1
			tokenList = { Token(TokenType::FLOAT, 5.1f), Token(TokenType::ADD), Token(TokenType::FLOAT, 3.1f) };
			node = make_shared<AST>(parser.GetNodeExp(tokenList.begin(), tokenList.end()));
			result = cal.Calculate(node, varList);
			Assert::AreEqual(result, 8.2f, L"5.1+3.1=8.2");

			// 5.1 + 3
			tokenList = { Token(TokenType::FLOAT, 5.1f), Token(TokenType::ADD), Token(TokenType::INT, 3) };
			node = make_shared<AST>(parser.GetNodeExp(tokenList.begin(), tokenList.end()));
			result = cal.Calculate(node, varList);
			Assert::AreEqual(result, 8.1f, L"5.1+3=8.1");

			// var(5) + 1
			varList.insert(std::pair<std::string, float>("var", 5));
			tokenList = { Token(TokenType::VAR, "var"), Token(TokenType::ADD), Token(TokenType::INT, 1) };
			node = make_shared<AST>(parser.GetNodeExp(tokenList.begin(), tokenList.end()));
			result = cal.Calculate(node, varList);
			Assert::AreEqual(result, 6.0f, L"var(5) + 1 = 8.1");

			// var(null) + 1
			varList = std::map<std::string, float>();
			tokenList = { Token(TokenType::VAR, "var"), Token(TokenType::ADD), Token(TokenType::INT, 1) };
			node = make_shared<AST>(parser.GetNodeExp(tokenList.begin(), tokenList.end()));
			result = cal.Calculate(node, varList);
			Assert::AreEqual(cal.GetErrorReport().size(), size_t(1), L"var(null) + 1 = 8.1");
		}

		TEST_METHOD(Test_AddVar)
		{
			Calculator cal;
			map<string, float> varList;
			Scanner scanner("var = 5.0");
			Parser parser(scanner.GetTokenList());

			auto test = parser.GetAST();
			cal.AddVar(parser.GetAST(), varList);
			Assert::AreEqual(varList.find("var")->first == "var", true, L"var = 5.0  ->  var");
			Assert::AreEqual(varList.find("var")->second == 5.0f, true, L"var = 5.0  ->  5.0");
			
		}
	};
}