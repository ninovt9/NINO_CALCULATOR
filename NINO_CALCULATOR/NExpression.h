#pragma once

#include "NScanner.h"
#include "NParser.h"

#include <string>
#include <vector>

//���ʽ

class NExpression
{
public:
	NExpression();
	~NExpression();

	//��ֵ
	static float Calculate(std::string expression);
};

