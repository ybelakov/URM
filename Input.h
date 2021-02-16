#pragma once
#include <string>
class Input
{
private:
	std::string input; // INC 
	std::string id1; 
	std::string id2; 
	std::string id3; 
    bool isInstruction; 
	bool isComment;
public:
	Input(std::string newInput, std::string newId1, std::string newId2, std::string newId3, bool newIsinstruction,bool newIscomment);
	std::string getInput();
	std::string getId1();
	std::string getId2();
	std::string getId3();
	bool getIsInstruction();
};

