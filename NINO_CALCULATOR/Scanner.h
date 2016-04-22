#pragma once

#include "Token.h"
#include "Dictionary.h"

#include <sstream>
#include <string>

namespace calculator
{

	enum class State
	{
		START,
		NUMBER,
		OPERATOR,
		END,
	};

	class Scanner
	{
		//����class
		//���ļ�������ȡtoken(GetNextToken)
	public:
		Scanner(const std::string &expression);
		//��ȡ�ļ�������������
	public:
		char GetNextChar();
		Token GetNextToken();	
			//���ȣ������׸��������׼�������ĸ���жϣ��ó���Ӧ״̬
			//����switch������Ӧ״̬�Ĵ�����
				//�˴�Ӧ���У����֣�������С������operator����Ч�ַ�������
				//�ڴ�����ŵ�ʱ��ʹ��dictionary����ѯ�͵���
			//���Ϲ�������Ӧ���ӽ�buffer_
			//��󷵻�token_;
	public:
		State HandleStartState();
		

	private:
		State state_;						//��ǰ״̬������״̬��
		std::stringstream expression_;		//���ʽ(����
		std::string buffer_;				//��ʱ����(�൱��tempStr)
		Token token_;						//��ʱtoken
	};

}




