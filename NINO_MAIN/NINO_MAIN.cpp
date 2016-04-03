// NINO_MAIN.cpp : �������̨Ӧ�ó������ڵ㡣
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


//���ü�����
void NCalculator()
{
	string line;
	cout << "\n��������ʽ: " << endl;
	cin >> line;

	auto result = NExpression::Calculate(line);

	cout << "���Ϊ��" << result << endl;
}

int main()
{
	for (;;)
	{
		try {
			NCalculator();
		}
		catch (invalid_argument err){
			cout << "����" << err.what() << endl;
		}
	}

	system("pause");
    return 0;
}

