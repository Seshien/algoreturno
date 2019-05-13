#pragma once
class UndirectedGraf
{
public:
	UndirectedGraf();

	UndirectedGraf(const std::vector<std::pair<int, int>>& eL, size_t V);

	~UndirectedGraf();

	void init(const std::vector<std::pair<int, int>>& eL, size_t V);

	std::vector<int> roberts();		// Krypton

	std::vector<int> flores();			// Polon

	void show();

	bool addConnection(const std::pair<int, int> & c);

	bool removeConnection(const std::pair<int, int> & c);

	int getSize()const;


private:
	std::vector<std::vector<int>> matrix;

	std::vector<int> _roberts(int wierz, std::vector<int> next, int depth);
	bool inStack(std::vector<int> S, int temp);
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

	std::vector<int> roberts();		// Krypton

	std::vector<int> flores();			// Polon

	void show();

	bool addConnection(const std::pair<int, int> & c);

	bool removeConnection(const std::pair<int, int> & c);

	int getSize()const;


private:
	std::vector<std::vector<int>> elListo;
	std::vector<int> _roberts(int wierz, std::vector<int> next,int depth);
	bool inStack(std::vector<int> S, int temp);
	std::vector<int> getVertices();
	std::vector<int> getNeighbours(int v);
	int getEven();


};