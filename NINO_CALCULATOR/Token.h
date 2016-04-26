#pragma once

#include <string>

namespace calculator
{
	enum class TokenType 
	{
		INT,
		FLOAT,
		ADD,		// +
		SUB,		// -
		MUL,		// * 
		DIV,		// /
		LEFT_PAR,	// (
		RIGHT_PAR,	// )

		INVALID,	// ��Ч����
	};

	class Token 
	{
	public:
		Token();
		Token(TokenType type);
		Token(TokenType type, int intValue);

	public:
		TokenType GetType();
		int GetIntValue();

	private:
		TokenType type_;
		int intValue_;
	};

	inline TokenType Token::GetType()
	{
		return type_;
	}

	inline int Token::GetIntValue()
	{
		return intValue_;
	}
}

