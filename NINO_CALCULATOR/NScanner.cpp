#include "stdafx.h"
#include "NScanner.h"

using std::vector;
using std::string;
using std::regex_match;
using std::smatch;

//ƥ�亯��
bool NIsTokenMatchRegex(string token)
{
	smatch result;
	if (regex_match(token, result, MULT_NUMBER_REGEX))			//����
		return true;
	else if (regex_match(token, result, OPERATOR_REGEX))		//�����
		return true;
	else if (regex_match(token, result, BRAKET_REGEX))			//����
		return true;
	else
		return false;
}

//�ֽⵥ����
vector<string> NGetTokenList(string line)
{
	vector<string> tokenList;
	string token = "";

	for (auto iter = line.begin(); iter != line.end(); ++iter)
	{
		//�ų��ո�
		if (*iter != ' ')
		{
			//ƥ�����
			if (!NIsTokenMatchRegex(token + *iter))
			{
				tokenList.push_back(token);
				//����
				token = *iter;

			}
			//����ƥ��
			else
			{
				token.push_back(*iter);
			}
		}	
	}
	//�������µ���
	if (token != "")
	{
		tokenList.push_back(token);
	}

	return tokenList;
}


//vector<string> NGetTokenList(string line)
//{
//
//	vector<string> resultVector;
//	string number;
//	smatch token;
//
//	for (auto each : line)
//	{
//		string temp;
//		temp.push_back(each);
//
//		//��������
//		if(regex_match(temp, token, SINGLE_NUMBER_REGEX))
//		{
//			number.append(token.str());	//�ϲ�����
//		}
//		//���������->��������
//		else if(regex_match(temp, token, OPERATOR_REGEX))
//		{
//			resultVector.push_back(number);			//��������
//			number = "";
//			resultVector.push_back(token.str());	//���������
//		}
//		else
//		{
//			;
//		}
//	}
//
//	//����ĩβ����
//	if (number != "")
//	{
//		resultVector.push_back(number);			//��������
//	}
//
//	return resultVector;
//}
