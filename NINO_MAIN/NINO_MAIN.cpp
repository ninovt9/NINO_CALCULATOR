// NINO_MAIN.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "NExpression.h"
#include <iostream>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::invalid_argument;


//调用计算器
void NCalculator()
{
	string line;
	cout << "\n请输入表达式: " << endl;
	cin >> line;

	auto result = NExpression::Calculate(line);

	cout << "结果为：" << result << endl;
}

int main()
{
	for (;;)
	{
		try {
			NCalculator();
		}
		catch (invalid_argument err){
			cout << "错误：" << err.what() << endl;
		}
	}

	system("pause");
    return 0;
}

