#include "Input.h"
#include<iostream>
using namespace std;
Input::Input(std::string newInput, std::string newId1, std::string newId2, std::string newId3, bool newInstruction,bool newIsComment)
{
	input = newInput;
	id1 = newId1;
	id2 = newId2;
	id3 = newId3;
	isInstruction = newInstruction;
	isComment = newIsComment;
}

std::string Input::getInput()
{
	return input;
}

std::string Input::getId1()
{
	return id1;
}

std::string Input::getId2()
{
	return id2;
}

std::string Input::getId3()
{
	return id3;
}

bool Input::getIsInstruction()
{
	return isInstruction;
}


