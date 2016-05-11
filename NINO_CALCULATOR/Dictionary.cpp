#include "stdafx.h"
#include "Dictionary.h"


using std::string;
using std::pair;



namespace calculator
{
	Dictionary::Dictionary()
	{
		AddToken(dict_, "+", Token(TokenType::ADD));
		AddToken(dict_, "-", Token(TokenType::SUB));
		AddToken(dict_, "*", Token(TokenType::MUL));
		AddToken(dict_, "/", Token(TokenType::DIV));
		AddToken(dict_, "(", Token(TokenType::LEFT_PAR));
		AddToken(dict_, ")", Token(TokenType::RIGHT_PAR));
		AddToken(dict_, "=", Token(TokenType::ASSIGNED));
		AddToken(dict_, "int", Token(TokenType::TYPE_INT));
		AddToken(dict_, "float", Token(TokenType::TYPE_FLOAT));
	}

	void Dictionary::AddToken(SyntaxDict &dict, const string &name, const Token &token)
	{
		dict.insert(pair<std::string, Token>(name, token));
	}

	bool Dictionary::HasToken(const string &name) const
	{
		return (dict_.find(name) != dict_.end());
	}

	Token Dictionary::FindToken(const string &name) const
	{
		auto iter = dict_.find(name);
		if (iter != dict_.end())
		{
			return iter->second;
		}
		else
		{
			return Token(TokenType::INVALID);
		}
	}

	
}