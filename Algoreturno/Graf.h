#pragma once
class UndirectedGraf
{
public:
	UndirectedGraf();

	UndirectedGraf(const std::vector<std::pair<int, int>>& eL, size_t V);

	~UndirectedGraf();

	void init(const std::vector<std::pair<int, int>>& eL, size_t V);

	void robercik();		// Krypton

	std::vector<int> flores();			// Polon

	void show();

	bool addConnection(const std::pair<int, int> & c);

	bool removeConnection(const std::pair<int, int> & c);

	int getSize()const;


private:
	std::vector<std::vector<int>> matrix;

	std::vector<int> getVertices();
	std::vector<int> getNeighbours(int v);
	int getEven();

	int DFSb(int v, int vf, std::vector<int> & D, int & cv);

};



class DirectedGraf
{
public:
	DirectedGraf();

	DirectedGraf(const std::vector<std::pair<int, int>>& eL, size_t V);

	~DirectedGraf();

	void init(const std::vector<std::pair<int, int>>& eL, size_t V);

	void robercik();		// Krypton

	std::vector<int> flores();			// Polon

	void show();

	bool addConnection(const std::pair<int, int> & c);

	bool removeConnection(const std::pair<int, int> & c);

	int getSize()const;


private:
	std::vector<std::vector<int>> elListo;

	std::vector<int> getVertices();
	std::vector<int> getNeighbours(int v);
	int getEven();

};