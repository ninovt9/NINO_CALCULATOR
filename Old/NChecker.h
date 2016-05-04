#pragma once

#include "NScanner.h"
#include "NParser.h"
#include <stdexcept>

#include <string>

//´íÎó¼ì²é
void NCheckError(std::string expression);		//Ö÷º¯Êı

void NCheckTokenError(std::string expression);	//µ¥´Ê´íÎó
void NCheckMatchError(std::string expression);	//À¨ºÅÆ¥Åä´íÎó
void NCheckOperatorAdjacent(std::string expression);	//ÔËËã·ûÏàÁÚ´íÎó

