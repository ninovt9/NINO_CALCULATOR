#pragma once

#include "Token.h"

#include <map>
#include <string>



namespace calculator
{
	//Óï·¨×Öµä
	using SyntaxDict = std::map<std::string, Token>;	

	class Dictionary
	{
	public:
		Dictionary();

	public:
		static void AddToken(SyntaxDict &dict, const std::string &name, Token token);

	public:
		bool HasToken(const std::string &name) const;
		Token FindToken(const std::string &name) const;

	private:
		SyntaxDict dict_;
		
	};
}



