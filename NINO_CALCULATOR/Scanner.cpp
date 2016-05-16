#include "stdafx.h"
#include "Scanner.h"

using std::string;
using std::vector;
using std::stringstream;

namespace calculator
{
	Scanner::Scanner() 
		: state_(State::START), dict_(), stream_("")
	{
	}

	Scanner::Scanner(const string &expression)
		: state_(State::START), dict_(), stream_(expression)
	{
	}

	char Scanner::GetNextChar(stringstream &expression)
	{
		char result;
		// strip space
		do {
			result = expression.get();
		} while (result == ' ');

		return result;
	}

	vector<Token> Scanner::GetNextTokenList(stringstream &expression)
	{
		vector<Token> result;

		while (expression.peek() != -1)
		{
			// if the next char is a line break
			if (expression.peek() == '\n')
			{
				expression.get();	// delete line break
				return result;
			}
			else
			{
				result.push_back(GetNextToken(expression));
			}
		}

		return result;
	}

	Token Scanner::GetNextToken(stringstream &expression)
	{
		// first char
		auto currectChar = GetNextChar(expression);

		// state judge
		while (!expression.eof())
		{
			switch (state_)
			{
			case State::START:
				break;

			case State::NUMBER:
				return HandleNumberState(expression, currectChar);
				break;

			case State::OPERATOR:
				return HandleOperatorState(expression, currectChar);
				break;

			case State::VARIABLE:
				return HandleVariableState(expression, currectChar);
				break;

			case State::ERROR:
				ErrorToken("error input", errorReport_);
				return Token(TokenType::INVALID);
			}

			string currectStr;
			currectStr.push_back(currectChar);

			//state迁移

			if (iswdigit(currectChar))
			{
				state_ = State::NUMBER;
			}
			else if (dict_.HasToken(currectStr))
			{
				state_ = State::OPERATOR;
			}
			else if (isalpha(currectChar))
			{
				state_ = State::VARIABLE;
			}
			else
			{
				state_ = State::ERROR;
			}
		}
		return Token(TokenType::INVALID);
	}


	Token Scanner::HandleNumberState(stringstream &expression, char currectChar)
	{
		// 问题：
			// 1.判断: 2a~~2.a 之类
			// 2.051 怎么办？

		Token result;

		// first char
		string buffer;
		buffer.push_back(currectChar);

		// int part
		while (!expression.eof() && isdigit(expression.peek()))
		{
			buffer += GetNextChar(expression);
		}
		
		if (expression.peek() != '.')
		{
			// string to int
			int intValue;
			std::stringstream stream(buffer);
			stream >> intValue;

			result = Token(TokenType::INT, intValue);
		}
		// float part
		else
		{
			// add dot
			buffer += GetNextChar(expression);

			while (!expression.eof() && isdigit(expression.peek()))
			{
				buffer += GetNextChar(expression);
			}

			// string to float
			float floatValue;
			std::stringstream stream(buffer);
			stream >> floatValue;

			result = Token(TokenType::FLOAT, floatValue);
		}

		state_ = State::START;

		return result;

		
	}

	Token Scanner::HandleOperatorState(stringstream &expression, char currectChar)
	{
		// first char
		string buffer;
		buffer.push_back(currectChar);
		auto token = dict_.FindToken(buffer);

		//reset state
		state_ = State::START;

		return token;
	}

	Token Scanner::HandleVariableState(stringstream &expression, char currectChar)
	{
		// first char
		string buffer;
		buffer.push_back(currectChar);
		
		while (!expression.eof() && isalpha(expression.peek()))
		{
			buffer += GetNextChar(expression);
		}

		// var_name
		auto token = Token(TokenType::VAR, buffer);

		//reset state
		state_ = State::START;

		return token;
	}


}






