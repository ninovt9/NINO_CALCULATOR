#pragma once

//�ʷ�����
//Ŀ�ģ������ʽ�ֽ�Ϊtoken

#include <string>
#include <vector>
#include <regex>

//������
extern std::vector<std::string> NGetTokenList(std::string line);

//������ʽ����

//����
const std::regex MULT_NUMBER_REGEX("[1-9][0-9]*|0|[0-9]+\\.[0-9]+"); //�����ж϶�λ����(������0��С����
const std::regex SINGLE_NUMBER_REGEX("[0-9]|\\."); //�����жϵ�λ����(0-9��С���㣩
//�ո�
const std::regex SPACE_REGEX("\\s+");
//��������
const std::regex OPERATOR_REGEX("\\+|\\-|\\*|\\/");	//�Ӽ��˳����ݶ���