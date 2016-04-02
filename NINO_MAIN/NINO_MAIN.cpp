// NINO_MAIN.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "NParser.h"
#include "NScanner.h"
#include <iostream>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;


//调用计算器
void NCalculator()
{
	string line;
	cout << "\n请输入表达式: " << endl;
	cin >> line;

	//分解
	vector<string> tokenList = NGetTokenList(line);
	//计算结果
	auto result = NEvaluateExpression(tokenList);

	cout << "结果为：" << result << endl;
}

int main()
{
	for (;;)
	{
		NCalculator();
	}

	system("pause");
    return 0;
}

