#pragma once
class AdjacencyMatriceGraph
{
public:
	AdjacencyMatriceGraph(const std::vector<std::pair<int, int>> & eL, size_t V);
	~AdjacencyMatriceGraph();

	// Inherited via GrafRepresentation
	//virtual void show() const override;
	void show();
	bool addConnection(const std::pair<int, int> & c);

	std::vector<std::pair<int, int>> toList();

private:
	std::vector<std::vector<int>> matrix;

	//virtual std::vector<int> getVertices()const override;
	//virtual std::vector<int> getNeighbours(int v)const override;

	std::vector<int> getVertices();
	std::vector<int> getNeighbours(int v);


};

