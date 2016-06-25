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
		ASSIGNMENT,	// =

		VAR,		// var_name

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
		Token(TokenType type, std::string varName, float coefficient);

	public:
		Token(const Token& other);
		Token& operator=(const Token& other);
		bool operator==(const Token& other);
		bool operator==(const Token& other) const;

	public:
		TokenType			GetType() const;
		int					GetIntValue() const;
		float				GetFloatValue() const;
		std::string			GetVarName() const;
		float				GetCoefficient() const;
		float				AddCoefficient(float value);

	private:
		TokenType			type_;
		int					intValue_;
		float				floatValue_;
		std::string			varName_;
		float				coefficient_;

	
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

	inline std::string Token::GetVarName() const
	{
		return varName_;
	}

	inline float Token::GetCoefficient() const
	{
		return coefficient_;
	}

	inline float Token::AddCoefficient(float value)
	{
		coefficient_ += value;
		return coefficient_;
	}

	inline bool IsNumber(Token token)
	{
		return (token.GetType() == TokenType::INT ||
				token.GetType() == TokenType::FLOAT);
	}

	inline bool IsOperator(Token token)
	{
		return (token.GetType() == TokenType::ADD ||
				token.GetType() == TokenType::SUB ||
				token.GetType() == TokenType::MUL ||
				token.GetType() == TokenType::DIV);
	}
}

