#include "pch.h"
#include <iostream>

int main()
{
	std::vector<std::pair<int, int>> v;
	//genGraf(1000, 20);
	//On zwraca liste krawedzi
	v=simplifiedGen(10, 50);
	//Tutaj sie tworzy lista nastepnikow skierowana
	AdjacencyListGraph list(v,10);
	//Tutaj sie tworzy matryca nieskierowana
	AdjacencyMatriceGraph matrix(v, 10);
	list.show();
	matrix.show();

	showEdges(v);
    std::cout << "Hello World!\n"; 
}
