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
		Scanner() = default;
		Scanner(const std::string &expression);

	public:
		//char GetNextChar();
		char GetNextChar(std::stringstream &expression);
		Token GetNextToken();	
		std::vector<Token> GetTokenList();

	public:
		void HandleNumberState();
		void HandleOperatorState();
		
	private:
		char currectChar_;					//��ǰ�ַ�
		Dictionary dict_;					//�﷨�ֵ�
		State state_;						//��ǰ״̬������״̬��
		std::stringstream expression_;		//���ʽ(����
		std::string buffer_;				//��ʱ����(�൱��tempStr)
		Token token_;						//��ʱtoken
	};

}




