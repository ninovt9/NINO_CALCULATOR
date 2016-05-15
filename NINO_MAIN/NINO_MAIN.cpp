// NINO_MAIN.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Calculator.h"

#include <iostream>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;


int main()
{
	//Expression expression = Expression();
	//std::string input;

	//for (;;)
	//{
	//	std::getline(cin, input);

	//	expression = Expression(input);
	//	cout << ">>" << expression.GetResult() << endl;
	//	cout << endl;
	//}
	
	calculator::Calculator cal;
	cal.Run();

	system("pause");
    return 0;
}

