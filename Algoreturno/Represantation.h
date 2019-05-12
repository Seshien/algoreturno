#pragma once

class AdjacencyListGraph
{
public:
	AdjacencyListGraph();
	AdjacencyListGraph(const std::vector<std::pair<int, int>> & eL, size_t V);
	~AdjacencyListGraph();

	void show();

private:
	std::vector<std::vector<int>> elListo;

	std::vector<int> getVertices();
	std::vector<int> getNeighbours(int v);

};
