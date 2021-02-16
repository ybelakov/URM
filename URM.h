#pragma once
#include<unordered_map>
#include <fstream>
#include "Input.h"
class URM 
{
//private:
public:
	std::unordered_map<int, int> memory;
	std::list<Input> inputList;
public:
	//Test functions
	void insertAt(int index,int value);
	//Instructions
	void zeroAt(int index);						//1
	void incAt(int index);						//2
	void moveAt(int x, int y);					//3
	void jumpAt(int x, int y, int z);			//5		
	void jumpFake(int z);

	//Commands
	void zeroFromTo(int x, int y);				//2.1      /zero x y
	void set(int x, int y);						//2.2      /set x y
	void copyFromTo(int x, int y, int z);		//2.3      /copy x y z
	void printFromTo(int x, int y);				//2.4      /mem x y

	void parser();
	int instrCounter();
	void runJumpCmd(int z);
	void commandRunner(std::list<Input>::iterator& it);
	void readFromFile(std::string Filename);
	bool isNumber(std::string string);
	void addComment(std::string string);
	bool hasInstr();
};

