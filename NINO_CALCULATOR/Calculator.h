#pragma once

#include "Expression.h"

#include <map>
#include <iostream>


namespace calculator
{
	// 计算器
	// 构造函数做初始化
	// 需要初始化一个符号表，存储变量（varList）dd
	// Run() 中循环进行Scanner + Parser;
	// auto 一个parser 
	// parser得出AST
	// 解析树
	// exp以下得出结果，sen添加varList

	// void 解析
		// float 计算 先用exp的
		// 赋值


	class Calculator
	{
	public:
		Calculator();
	public:
		std::string Analyze(const AST& ast);
		void Assigned(const AST& ast, std::map<std::string, float>& varList_);
		float Calculate(std::shared_ptr<AST> node);
		void Run();
	private:
		std::map<std::string, float> varList_;
		std::string input_;
		AST ast_;

	};
}


