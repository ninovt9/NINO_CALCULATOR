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
	public:
		TokenType GetType();
		
	private:
		TokenType type_;
	};

	inline TokenType Token::GetType()
	{
		return type_;
	}
}

