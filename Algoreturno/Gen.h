#pragma once
#include "pch.h"

bool createR(std::vector<std::pair<int, int>> & relations, size_t nodes, bool cyclesearch = false);
bool createN(std::vector<std::pair<int, int>> & relations, int node1, int node2, bool cyclesearch = false);

//std::vector<std::pair<int, int>> simplifiedGen(int n, int sat);

bool multiSearch(const std::vector<std::pair<int, int>> & relations);

std::vector<std::pair<int, int>> loadGraf(size_t & number);


std::vector<std::pair<int, int>> manualGraf(size_t & number);


std::vector<std::pair<int, int>> genGraf(int amount, int nas);


void showEdges(const std::vector<std::pair<int, int>> & relations);