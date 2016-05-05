#include "stdafx.h"
#include "Token.h"

namespace calculator
{
	Token::Token() : type_(TokenType::INVALID), intValue_(0)
	{

	}

	Token::Token(TokenType type) : type_(type), intValue_(0)
	{

	}

	Token::Token(TokenType type, int intValue) : type_(type), intValue_(intValue)
	{

	}

	Token::Token(const Token& other)
	{
		type_ = other.type_;
		intValue_ = other.intValue_;
	}

	Token& Token::operator=(const Token& other)
	{
		type_ = other.type_;
		intValue_ = other.intValue_;
		return *this;
	}

	bool Token::operator==(const Token& other)
	{
		return (
			type_ == other.type_
			&&  intValue_ == other.intValue_
			);
	}
}