#include "URM.h"
#include<iostream>
void URM::insertAt(int index,int value)
{
	memory[index] = value;
}

void URM::zeroAt(int index)
{
	memory.erase(index);
}

void URM::incAt(int index)
{
	memory[index] += 1;
}

void URM::moveAt(int x, int y)
{
	memory[y] = memory[x];
}

void URM::jumpAt(int x, int y, int z)
{
	if (instrCounter() < z + 1)
	{
		return;
	}
	else
	{
		if (x == y)
		{
			std::list<Input>::iterator it;
			int counter = 0;
			while (counter != z)
			{
				if (it->getIsInstruction() == true)
				{
					counter++;
				}
				it++;
			}
		}
		else
		{
			return;
		}
	}
}

void URM::jumpFake(int z)
{
	jumpAt(0, 0, z);
}

void URM::zeroFromTo(int x, int y)
{
	
		for (int i = x; i <= y; i++)
		{
			memory.erase(i);
		}
}

void URM::set(int x, int y)
{
	memory[x] = y;
}

void URM::copyFromTo(int x, int y, int z)
{
	while (z > 0)
	{
		memory[y] = memory[x];
		x++;
		y++;
		z--;
	}
}

void URM::printFromTo(int x, int y)
{
	for (int i = x; i <= y; i++)
	{
		if (memory[i] != 0)
		{
			std::cout << "Index = " << i << " , value = " << memory[i] << std::endl;
		}
	}
}

void URM::parser()
{
	while (1)
	{
		std::cout << "Enter command/instruction" << std::endl;
		std::string input;
		std::getline(std::cin, input);
		std::string delimiter = " ";
		size_t current, previous = 0;

		current = input.find(delimiter);
		std::string cmd = input.substr(previous, current - previous);
		previous = current + 1;
		current = input.find(delimiter, previous);
		std::string id1 = input.substr(previous, current - previous);
		previous = current + 1;
		current = input.find(delimiter, previous);
		std::string id2 = input.substr(previous, current - previous);
		previous = current + 1;
		current = input.find(delimiter, previous);
		std::string id3 = input.substr(previous, current - previous);
		previous = current + 1;
		current = input.find(delimiter, previous);
		std::string id4 = input.substr(previous, current - previous);
		//std::cout << cmd << id1 << id2 << id3 << id4;

		//Instructions
		if (cmd.compare("ZERO") == 0)
		{
			Input newInput(cmd, id1, "", "", true, false);
			inputList.push_back(newInput);
			zeroAt(stoi(id1));
		}
		else if (cmd.compare("INC") == 0)
		{
			Input newInput(cmd, id1, "", "", true, false);
			inputList.push_back(newInput);
			incAt(stoi(id1));
		//	std::cout << cmd << " " << id1;
		}
		else if (cmd.compare("MOVE") == 0)
		{
			Input newInput(cmd, id1, id2, "", true, false);
			inputList.push_back(newInput);
			moveAt(stoi(id2), stoi(id1));
		}
		else if (cmd.compare("JUMP") == 0)
		{
			if (input.size() < 10)
			{
				if (instrCounter() >= stoi(id1))
				{
					Input newInput(cmd, id1, "", "", true, false);
					inputList.push_back(newInput);
					std::list<Input>::iterator temp = inputList.begin();
					//	std::cout << cmd << " " << id1 << " " << id2 << " " << id3;
					if (std::stoi(id1) == 0)
					{
						temp = inputList.begin();
						//temp++;
					}
					else
					{
						int counter = 1;
						while (counter != (std::stoi(id1)))
						{
							if (temp->getIsInstruction())
							{
								counter++;
							}
							temp++;
						}
					}
					commandRunner(temp);
				}
				else
				{
					return;
				}
			}
			else
			{
				if (memory[stoi(id1)] == memory[stoi(id2)])
				{
						if (instrCounter() >= stoi(id3))
						{
							Input newInput(cmd, id1, id2, id3, true, false);
							inputList.push_back(newInput);
							std::list<Input>::iterator temp = inputList.begin();
							//std::cout << cmd << " " << id1 << " " << id2 << " " << id3;
							if (std::stoi(id3) == 0)
							{
								temp = inputList.begin();
								//temp++;
							}
							else
							{
								int counter = 1;
								while (counter != (std::stoi(id3)))
								{
									if (temp->getIsInstruction())
									{
										counter++;
									}
									temp++;
								}
							}
								commandRunner(temp);
						}
						else
						{
							return;
						}
				}
				else
				{
					Input newInput(cmd, id1, id2, id3, true, false);
					inputList.push_back(newInput);
					std::list<Input>::iterator temp = inputList.begin();
					continue;
				}
			}
		}
		//Commands
		else if (cmd.compare("/zero") == 0)
		{
			Input newInput(cmd, id1, id2, "", false, false);
			inputList.push_back(newInput);
			zeroFromTo(stoi(id1), stoi(id2));
		}
		else if (cmd.compare("/set") == 0)
		{
			Input newInput(cmd, id1, id2, "", false, false);
			inputList.push_back(newInput);
			set(stoi(id1), stoi(id2));
		//	std::cout << cmd << " " << id1 << " " << id2;
		}
		else if (cmd.compare("/copy") == 0)
		{
			Input newInput(cmd, id1, id2, id3, false, false);
			inputList.push_back(newInput);
			copyFromTo(stoi(id1), stoi(id2), stoi(id3));
		}
		else if (cmd.compare("/mem") == 0)
		{
			Input newInput(cmd, id1, id2, "", false, false);
			inputList.push_back(newInput);
			printFromTo(stoi(id1), stoi(id2));
		}
		else if (cmd.compare("/load") == 0)
		{
			inputList.clear();
			readFromFile(id1);
		}
		else if (cmd.compare("/add") == 0)
		{
			readFromFile(id1);
		}
		else if (cmd.compare("/run") == 0)
		{
			std::list<Input>::iterator a = inputList.begin();
			commandRunner(a);
		}
		else if (cmd.compare("/code") == 0)
		{
			std::list<Input>::iterator a;
			for (a = inputList.begin(); a != inputList.end(); a++)
			{
				if (a->getInput() == "/comment")
				{
					std::cout << "/comment " << a->getId1() << std::endl;
				}
				else
				{
					std::cout << a->getInput() << " " << a->getId1() << " " << a->getId2() << " " << a->getId3() << std::endl;
				}
			}
		}
		else if (cmd.compare("/comment") == 0)
		{
			addComment(id1);
		}
		else if (cmd.compare("/quote") == 0)
		{
			if (id1.compare("INC") == 0 || id1.compare("ZERO") == 0)
			{
				Input newInput(id1, id2, "", "", 1, 0);
				inputList.push_back(newInput);
			}
			else if (id1.compare("/set") == 0 || id1.compare("/copy") == 0 || id1.compare("/mem") == 0)
			{
				if (id1.compare("/copy") == 0)
				{
					Input newInput(id1, id2, id3, id4, 0, 0);
					inputList.push_back(newInput);
				}
				else 
				{
					Input newInput(id1, id2, id3, "", 0, 0);
					inputList.push_back(newInput);
				}
			}
			else if (id1.compare("MOVE") == 0)
			{
				Input newInput(id1, id2, id3, "", 1, 0);
				inputList.push_back(newInput);
			}
			else if (id1.compare("JUMP") == 0)
			{
				if (input.size() <= 15)
				{
					Input newInput(id1, id2, "", "", 1, 0);
					inputList.push_back(newInput);
				}
				else
				{
					Input newInput(id1, id2, id3, id4, 1, 0);
					inputList.push_back(newInput);
				}
			}
		}
		else if (cmd.compare("EXIT") == 0)
		{
			return;
		}
		else
		{
			std::cout << "Enter command/instruction" << std::endl;
			std::getline(std::cin, input);
		}
	}
}

int URM::instrCounter()
{
	int counter = 0;
	std::list<Input>::iterator it;
	for (it = inputList.begin(); it != inputList.end(); ++it) {
		if (it->getIsInstruction() == true)
		{
			counter++;
		}
	}
	return counter;
}

void URM::runJumpCmd(int z)
{
	std::list<Input>::iterator temp = inputList.begin();
	int counter = 0;
	while (counter != z)
	{
		if (temp->getIsInstruction())
		{
			counter++;
		}
		temp++;
	}
	temp--;

}

void URM::commandRunner(std::list<Input>::iterator& it)
{
	while (it != inputList.end())
	{
		//ZERO
		if (it->getInput().compare("ZERO") == 0)
		{
			zeroAt(stoi(it->getId1()));
			it++;
		}
		//INC
		else if (it->getInput().compare("INC") == 0)
		{
			incAt(stoi(it->getId1()));
			it++;
		}
		//MOVE
		else if (it->getInput().compare("MOVE") == 0)
		{
			moveAt(stoi(it->getId1()), stoi(it->getId2()));
			it++;
		}
		//JUMP
		else if (it->getInput().compare("JUMP") == 0)
		{
				if (it->getId2().compare("") == 0)
				{
						if (instrCounter() > (stoi(it->getId1())))
						{
							std::list<Input>::iterator temp = inputList.begin();
							if ((stoi(it->getId1()) == 0))
							{
								it = inputList.begin();
								//it++;
							}
							else
							{
								int counter = 1;
								while (counter != (stoi(it->getId1())))
								{
									if (temp->getIsInstruction())
									{
										counter++;
									}
									temp++;
								}
								it = temp;
							}
						}
						else
						{
							return;
						}
				}
				else
				{
					if (memory[stoi(it->getId1())] == memory[stoi(it->getId2())])
					{
						if (instrCounter() > (stoi(it->getId3())))
						{
							std::list<Input>::iterator temp = inputList.begin();
							if ((stoi(it->getId3()) == 0))
							{
								it = inputList.begin();
								//it++;
							}
							else
							{
								int counter = 1;
								while (counter != (stoi(it->getId3())))
								{
									if (temp->getIsInstruction())
									{
										counter++;
									}
								temp++;
								}
								it = temp;
							}
						}
						else
						{
							return;
						}
					}
					else
					{
						it++;
						continue;
					}
				}
		}
		//Commands
		else if (it->getInput().compare("/zero") == 0)
		{
			zeroFromTo(stoi(it->getId1()), stoi(it->getId2()));
			it++;
		}
		else if (it->getInput().compare("/set") == 0)
		{
			set(stoi(it->getId1()), stoi(it->getId2()));
			it++;
		}
		else if (it->getInput().compare("/copy") == 0)
		{
			copyFromTo(stoi(it->getId1()), stoi(it->getId2()), stoi(it->getId3()));
			it++;
		}
		else if (it->getInput().compare("/mem") == 0)
		{
			printFromTo(stoi(it->getId1()), stoi(it->getId2()));
			it++;
		}
		else
		{
			it++;
			continue;
		}

	}
}

void URM::readFromFile(std::string fileName)
{
		std::ifstream in;
		in.open(fileName);
		int inputListSize;
		std::string input;
		std::string id1;
		std::string id2;
		std::string id3;
		bool isInstruction;
		bool isComment;
		in >> inputListSize;
		for (int i = 0; i < inputListSize; i++)
		{	
			in >> input;
			if (input.compare("INC") == 0 || input.compare("ZERO") == 0)
			{
				in >> id1 >> isInstruction >> isComment;
				id2 = id3 = "";
			}
			else if (input.compare("MOVE") == 0 || input.compare("/set") == 0 || input.compare("/copy") == 0
				|| input.compare("/mem") == 0)
			{
				in >> id1 >> id2 >> isInstruction >> isComment;
				id3 = "";
			}
			else if (input.compare("JUMP") == 0)
			{
				in >> id1;
				in >> id2; 
				if (isNumber(id2))
				{
					in >> id3 >> isInstruction >> isComment;
				}
				else
				{
					id2 = id3 = "";
					in >> isInstruction >> isComment;
				}
			}
			else
			{
				continue;
			}
			//std::cout << input << id1 << isInstruction;
			Input newInput(input, id1, id2, id3, isInstruction,isComment);
			inputList.push_back(newInput);
		}
		in.close();
}

bool URM::isNumber(std::string string)
{
		std::string::const_iterator it = string.begin();
		while (it != string.end() && std::isdigit(*it)) ++it;
		return !string.empty() && it == string.end();
}

void URM::addComment(std::string string)
{
	Input newInput("/comment", string, "", "", false, true);
	inputList.push_back(newInput);
}

bool URM::hasInstr()
{
	std::list<Input>::iterator it;
	for (it = inputList.begin(); it != inputList.end(); it++)
	{
		if (it->getIsInstruction())
		{
			return true;
	    }
		return false;
	}
}



