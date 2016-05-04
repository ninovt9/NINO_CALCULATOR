#pragma once

//�ʷ�����
//Ŀ�ģ������ʽ�ֽ�Ϊtoken

#include <string>
#include <vector>
#include <regex>

//������
extern std::vector<std::string> NGetTokenList(std::string line);
//ƥ�亯��
extern bool NIsTokenMatchRegex(std::string token);

//������ʽ����

//����
const std::regex SINGLE_NUMBER_REGEX("[0-9]|\\."); //�����жϵ�λ����(0-9��С���㣩
const std::regex MULT_NUMBER_REGEX("[1-9][0-9]*|0|[0-9]+\\.[0-9]*"); //�����ж϶�λ����(������0��С����
//��������
const std::regex OPERATOR_REGEX("\\+|\\-|\\*|\\/");	//�Ӽ��˳����ݶ���
//�ո�
const std::regex SPACE_REGEX("\\s+");
//����
const std::regex BRAKET_REGEX("\\(|\\)");



