#include "stdafx.h"
#include "NScanner.h"

using std::vector;
using std::string;
using std::regex_match;
using std::smatch;

vector<string> NGetTokenList(string line)
{

	vector<string> resultVector;
	string number;
	smatch token;

	for (auto each : line)
	{
		string temp;
		temp.push_back(each);

		//��������
		if(regex_match(temp, token, SINGLE_NUMBER_REGEX))
		{
			number.append(token.str());	//�ϲ�����
		}
		//���������->��������
		else if(regex_match(temp, token, OPERATOR_REGEX))
		{
			resultVector.push_back(number);			//��������
			number = "";
			resultVector.push_back(token.str());	//���������
		}
		else
		{
			;
		}
	}

	//����ĩβ����
	if (number != "")
	{
		resultVector.push_back(number);			//��������
	}

	return resultVector;
}
