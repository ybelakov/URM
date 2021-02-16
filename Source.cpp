#include<iostream>
#include<unordered_map>
#include"URM.h"
#include "Input.h"
using namespace std;



int main()
{
	URM URM;
	std::list<Input>::iterator a = URM.inputList.begin();
	URM.parser();
}		


