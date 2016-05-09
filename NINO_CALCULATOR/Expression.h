#pragma once

#include "Scanner.h"
#include "Parser.h"

namespace calculator
{
	class Expression
	{
	public:
		Expression() = default;
		Expression(const std::string &expression);

	public:
		const Expression& operator+(const Expression& other);
		const Expression& operator-(const Expression& other);
		const Expression& operator*(const Expression& other);
		const Expression& operator/(const Expression& other);

		// this.tree + operator + other.tree
		AST MergeAST(const Token& root, const AST& left, const AST& right);

		// is equal

	public:
		float GetResult();

	public:
		float Calculate(std::shared_ptr<AST> node);

	private:
		AST ast_;
		float result_;
	};

	inline float Expression::GetResult()
	{
		return result_;
	}

	inline AST Expression::MergeAST(const Token& root, const AST& left, const AST& right)
	{
		return AST(left, root, right);
	}

	inline const Expression& Expression::operator+(const Expression& other)
	{
		ast_ = MergeAST(Token(TokenType::ADD), ast_, other.ast_);
		result_ = Calculate(std::make_shared<AST>(ast_));

		return *this;
	}

	inline const Expression& Expression::operator-(const Expression& other)
	{
		ast_ = MergeAST(Token(TokenType::SUB), ast_, other.ast_);
		result_ = Calculate(std::make_shared<AST>(ast_));

		return *this;
	}

	inline const Expression& Expression::operator*(const Expression& other)
	{
		ast_ = MergeAST(Token(TokenType::MUL), ast_, other.ast_);
		result_ = Calculate(std::make_shared<AST>(ast_));

		return *this;
	}

	inline const Expression& Expression::operator/(const Expression& other)
	{
		ast_ = MergeAST(Token(TokenType::DIV), ast_, other.ast_);
		result_ = Calculate(std::make_shared<AST>(ast_));

		return *this;
	}

}



