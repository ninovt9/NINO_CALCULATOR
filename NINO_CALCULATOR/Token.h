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

		INVALID,	// 无效类型
	};

	class Token 
	{
	public:
		Token();
		Token(TokenType type);
		Token(TokenType type, int intValue);
		Token(TokenType type, float floatValue);
		Token(TokenType type, double doubleValue);

		// 先用float，有空改成double
		
	public:
		Token(const Token& other);
		Token& operator=(const Token& other);
		bool operator==(const Token& other);
		bool operator==(const Token& other) const;

	public:
		TokenType GetType() const;
		int GetIntValue() const;
		float GetFloatValue() const;

	private:
		TokenType type_;
		int intValue_;

		float floatValue_;
	};

	inline TokenType Token::GetType() const
	{
		return type_;
	}

	inline int Token::GetIntValue() const
	{
		return intValue_;
	}

	inline float Token::GetFloatValue() const
	{
		return floatValue_;
	}
}

