#include "stdafx.h"
#include "Scanner.h"

using std::string;

namespace calculator
{
	Scanner::Scanner(const string &expression):state_(State::START), buffer_("")
	{
		expression_ = std::stringstream(expression);
	}

	char Scanner::GetNextChar()
	{
		char ch;
		expression_ >> ch;
		return ch;
	}

	State Scanner::HandleStartState()
	{
		auto ch = GetNextChar();	//��ȡ��ǰ�ַ�
		Dictionary dict = Dictionary();
		
		//����:0-9					
		if (isdigit(ch))	
		{
			return State::NUMBER;
		}
		//�ַ�
		//elif(dict.FindToken())
	}

	Token Scanner::GetNextToken()
	{
		//״̬�ж�
		switch (state_)
		{
		case State::START:
			//����ĸ�ж�state
			break;
		case State::NUMBER:
			//���ִ���
			break;
		case State::OPERATOR:
			//���Ŵ���
			break;
		case State::END:
			//
			break;
		default:
			//
			break;
		}
	}
}




