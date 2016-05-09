#include "stdafx.h"
#include "Token.h"

namespace calculator
{
	Token::Token() : type_(TokenType::INVALID), intValue_(0), floatValue_(0.0f)
	{

	}

	Token::Token(TokenType type) : type_(type), intValue_(0), floatValue_(0.0f)
	{

	}

	Token::Token(TokenType type, int intValue) : type_(type), intValue_(intValue), floatValue_(0.0f)
	{

	}

	Token::Token(TokenType type, float floatValue) : type_(type), intValue_(0), floatValue_(floatValue)
	{

	}

	Token::Token(TokenType type, double doubleValue) : type_(type), intValue_(0), floatValue_(static_cast<float>(doubleValue))
	{

	}


	Token::Token(const Token& other)
	{
		type_ = other.type_;
		intValue_ = other.intValue_;
		floatValue_ = other.floatValue_;
	}

	Token& Token::operator=(const Token& other)
	{
		type_ = other.type_;
		intValue_ = other.intValue_;
		floatValue_ = other.floatValue_;
		return *this;
	}

	bool Token::operator==(const Token& other)
	{
		return (
			type_ == other.type_
			&& intValue_ == other.intValue_
			&& floatValue_ == other.floatValue_
			);
	}

	bool Token::operator==(const Token& other) const
	{
		return (
			type_ == other.type_
			&& intValue_ == other.intValue_
			&& floatValue_ == other.floatValue_
			);
	}
}