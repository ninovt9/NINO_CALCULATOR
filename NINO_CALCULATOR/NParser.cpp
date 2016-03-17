#include "stdafx.h"
#include "NParser.h"

using std::vector;
using std::string;
using std::find;

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

