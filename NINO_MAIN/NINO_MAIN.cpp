// NINO_MAIN.cpp : �������̨Ӧ�ó������ڵ㡣
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


//���ü�����
void NCalculator()
{
	string line;
	cout << "\n��������ʽ: " << endl;
	cin >> line;

	//�ֽ�
	vector<string> tokenList = NGetTokenList(line);
	//������
	auto result = NEvaluateExpression(tokenList);

	cout << "���Ϊ��" << result << endl;
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

