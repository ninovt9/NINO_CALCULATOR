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
		explicit Token();
		explicit Token(TokenType type);
		explicit Token(TokenType type, int intValue);
		
	public:
		Token(const Token& other);
		Token& operator=(const Token& other);
		bool operator==(const Token& other);

	public:
		TokenType GetType() const;
		int GetIntValue() const;

	private:
		TokenType type_;
		int intValue_;
	};

	inline TokenType Token::GetType() const
	{
		return type_;
	}

	inline int Token::GetIntValue() const
	{
		return intValue_;
	}
}

