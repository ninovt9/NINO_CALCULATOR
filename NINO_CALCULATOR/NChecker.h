#pragma once

#include "NScanner.h"
#include "NParser.h"
#include <stdexcept>

#include <string>

//������
void NCheckError(std::string expression);		//������

void NCheckTokenError(std::string expression);	//���ʴ���
void NCheckMatchError(std::string expression);	//����ƥ�����
void NCheckOperatorAdjacent(std::string expression);	//��������ڴ���

