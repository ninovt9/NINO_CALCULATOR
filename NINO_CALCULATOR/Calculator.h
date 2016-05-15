#pragma once

#include "Expression.h"

#include <map>
#include <iostream>


namespace calculator
{
	// ������
	// ���캯������ʼ��
	// ��Ҫ��ʼ��һ�����ű��洢������varList��dd
	// Run() ��ѭ������Scanner + Parser;
	// auto һ��parser 
	// parser�ó�AST
	// ������
	// exp���µó������sen���varList

	// void ����
		// float ���� ����exp��
		// ��ֵ


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


