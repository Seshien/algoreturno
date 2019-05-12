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
class AdjacencyListGraph
{
public:
	AdjacencyListGraph(const std::vector<std::pair<int, int>> & eL, size_t V);
	~AdjacencyListGraph();

	void show();

private:
	std::vector<std::vector<int>> elListo;

	std::vector<int> getVertices();
	std::vector<int> getNeighbours(int v);

};
