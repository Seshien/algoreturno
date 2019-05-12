#pragma once
#include "pch.h"

class GenGraf
{

public:
	GenGraf();

	~GenGraf();
	bool loadGraf(size_t & number);


	bool manualGraf(size_t & number);


	bool genGraf(int amount, int nas);

	bool clearGraf();

	bool ifEmpty();

	bool simplifiedGen(int n, int sat);

	void showEdges();

	std::vector<std::pair<int, int>> retGraf();

private:
	std::vector<std::pair<int, int>> generated;

	bool createR(size_t nodes);
	bool createN(int node1, int node2);

	bool multiSearch();

	bool addConnection(std::vector<std::vector<int>> & matrix, const std::pair<int, int>& c);


	std::vector<std::pair<int, int>> toList(std::vector<std::vector<int>> & matrix);
};






