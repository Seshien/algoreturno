#pragma once
class AdjacencyMatriceGraph
{
public:
	AdjacencyMatriceGraph(const std::vector<std::pair<int, int>> & eL, size_t V);
	~AdjacencyMatriceGraph();

	void show();
	bool addConnection(const std::pair<int, int> & c);

	std::vector<std::pair<int, int>> toList();

private:
	std::vector<std::vector<int>> matrix;

	std::vector<int> getVertices();
	std::vector<int> getNeighbours(int v);


};

