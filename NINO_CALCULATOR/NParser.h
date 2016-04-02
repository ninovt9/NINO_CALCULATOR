#pragma once

#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <sstream>


/*
�﷨����
*/

//������ʽ
extern float NEvaluateExpression(std::vector<std::string> expression);
//����������㺯��
extern float NEvaluateExpressionForE(std::vector<std::string> expression);	//E:�Ӽ���
extern float NEvaluateExpressionForF(std::vector<std::string> expression);	//T:�˳���
extern float NEvaluateExpressionForT(std::vector<std::string> expression);	//F:����
extern float NEvaluateExpressionForId(std::string number);					//id:�ս��

//���÷�Χ�Ƿ��������ڣ�������������ƥ�䣩
extern bool NIsInBracket(std::vector<std::string>::iterator begin,
						 std::vector<std::string>::iterator end);

//�Ƿ����ͨ���÷��ŷָ�
extern bool NIsSplitBySymbol(std::vector<std::string> &expression,
					         std::string n_operator,
					         std::vector<std::string>::iterator &iterSplit);

