// NINO_MAIN.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Expression.h"

#include <iostream>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;

using calculator::Expression;

int main()
{
	Expression expression = Expression();
	std::string input;

	for (;;)
	{
		std::getline(cin, input);

		expression = Expression(input);
		cout << ">>" << expression.GetResult() << endl;
		cout << endl;
	}


	system("pause");
    return 0;
}

