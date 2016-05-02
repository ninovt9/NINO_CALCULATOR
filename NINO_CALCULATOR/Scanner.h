#pragma once

#include "Token.h"
#include "Dictionary.h"

#include <sstream>
#include <string>
#include <vector>

namespace calculator
{

	enum class State
	{
		START,
		NUMBER,
		OPERATOR,
	};

	class Scanner
	{
	public:
		Scanner();
		Scanner(const std::string &expression);

	public:
		char GetNextChar(std::stringstream &expression);	
		Token GetNextToken(std::stringstream &expression);								
		std::vector<Token> GetTokenList(std::stringstream &expression);		
		std::vector<Token> GetTokenList()
		{
			return std::vector<Token>();
		}

	public:
		Token HandleNumberState(std::stringstream &expression, char currectChar);
		Token HandleOperatorState(std::stringstream &expression, char currectChar);
		
	private:
		char currectChar_;					//��ǰ�ַ�
		Dictionary dict_;					//�﷨�ֵ�
		State state_;						//��ǰ״̬������״̬��
		std::stringstream expression_;		//���ʽ(����
		std::string buffer_;				//��ʱ����(�൱��tempStr)
		Token token_;						//��ʱtoken
	};

}




