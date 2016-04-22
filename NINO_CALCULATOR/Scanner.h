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
		//构建class
		//从文件流中提取token(GetNextToken)
	public:
		Scanner(const std::string &expression);
		//读取文件流，并检测错误
	public:
		char GetNextChar();
		Token GetNextToken();	
			//首先，进行首个（或者首几个）字母的判断，得出相应状态
			//在用switch进入相应状态的处理函数
				//此处应该有：数字（整数、小数）、operator、无效字符。。。
				//在处理符号的时候，使用dictionary做查询和调用
			//符合规则的情况应该扔进buffer_
			//最后返回token_;
	public:
		State HandleStartState();
		

	private:
		State state_;						//当前状态，用于状态机
		std::stringstream expression_;		//表达式(流）
		std::string buffer_;				//临时缓存(相当于tempStr)
		Token token_;						//临时token
	};

}




