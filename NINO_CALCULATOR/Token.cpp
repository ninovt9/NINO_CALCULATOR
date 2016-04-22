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
}