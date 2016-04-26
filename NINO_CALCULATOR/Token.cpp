#include "stdafx.h"
#include "Token.h"

namespace calculator
{
	Token::Token() : type_(TokenType::INVALID)
	{

	}

	Token::Token(TokenType type) : type_(type)
	{

	}

	Token::Token(TokenType type, int intValue) : type_(type), intValue_(intValue)
	{

	}
}