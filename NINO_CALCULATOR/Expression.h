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
}



