#include "pch.h"
#include <iostream>

int main()
{
	std::vector<std::pair<int, int>> v;
	//genGraf(1000, 20);
	v=simplifiedGen(100, 50);
	showEdges(v);
    std::cout << "Hello World!\n"; 
}
