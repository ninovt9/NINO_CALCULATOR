#pragma once

#include "NScanner.h"
#include "NParser.h"
#include "NChecker.h"

#include <string>
#include <vector>

//表达式

class NExpression
{
public:
	NExpression();
	~NExpression();

	//求值
	static float Calculate(std::string expression);
};

