#include "stdafx.h"
#include "NParser.h"

using std::vector;
using std::string;
using std::find;
using std::stringstream;

//���÷�Χ�Ƿ��������ڣ�������������ƥ�䣩
bool NIsInBracket(vector<string>::iterator begin,
	vector<string>::iterator end)
{
	int count = 0;
	for (; begin != end; ++begin)
	{
		//������������������
		if (*begin == "(")
			count++;
		else if(*begin == ")")
			count--;
	}
	if (count <= 0)
		return false;
	else
		return true;
}

//���ʽ�Ƿ����ͨ����������ָ���ó�����������������ã�
bool NIsSplitBySymbol(vector<string> expression,
	string n_operator,
	vector<string>::iterator &iterSplit)
{
	for (iterSplit = expression.begin(); iterSplit != expression.end(); ++iterSplit)
	{
		if (*iterSplit == n_operator &&
			!NIsInBracket(expression.begin(), iterSplit))
			return true;
	}
	return false;
}

//E:�Ӽ���
float NEvaluateExpressionForE(vector<string> expression)
{
	auto iterSplit = expression.begin();
	//T+E
	if (NIsSplitBySymbol(expression, "+", iterSplit))
	{
		return NEvaluateExpressionForT(expression) + NEvaluateExpressionForE(expression);
	}
	//T-E
	else if (NIsSplitBySymbol(expression, "-", iterSplit))
	{
		return NEvaluateExpressionForT(expression) - NEvaluateExpressionForE(expression);
	}
	//����->T
	else
	{
		return NEvaluateExpressionForT(expression);
	}
}
//T:�˳���
float NEvaluateExpressionForT(vector<string> expression)
{
	auto iterSplit = expression.begin();
	//F*T
	if (NIsSplitBySymbol(expression, "*", iterSplit))
	{
		return NEvaluateExpressionForF(expression) + NEvaluateExpressionForT(expression);
	}
	//F/T
	else if (NIsSplitBySymbol(expression, "/", iterSplit))
	{
		return NEvaluateExpressionForF(expression) - NEvaluateExpressionForT(expression);
	}
	//����->F
	else
	{
		return NEvaluateExpressionForF(expression);
	}
}

//F:����
float NEvaluateExpressionForT(vector<string> expression)
{
	auto begin = expression.begin();
	auto end = expression.end() - 1;
	//����
	if (*begin == "(" && *end == ")")
	{
		//��ȡ�����м䲿��
		return NEvaluateExpressionForE(vector<string>(begin + 1, end - 1));
	}
	else
	{
		//����Ӧ���д������
		return NEvaluateExpressionForId(expression[0]);
	}
}

//id:�ս��
float NEvaluateExpressionForId(string number)
{
	float result;
	stringstream stream(number);
	stream >> result;
	return result;
}
