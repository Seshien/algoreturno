#include "pch.h"
#include "Represantation.h"

//tworzy macierz nieskierowan¹
AdjacencyMatriceGraph::AdjacencyMatriceGraph()
{

}

AdjacencyMatriceGraph::AdjacencyMatriceGraph(const std::vector<std::pair<int, int>>& eL, size_t V)
{
	matrix.resize(V);
	for (auto &x : matrix)
	{
		x.resize(V);
	}

	for (auto connection : eL)
	{
		matrix[connection.first][connection.second] = 1;
		matrix[connection.second][connection.first] = 1;
	}
}

AdjacencyMatriceGraph::~AdjacencyMatriceGraph()
{

}

std::vector<int> AdjacencyMatriceGraph::getVertices()
{
	std::vector<int> res;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		res.push_back(i);
	}
	return res;
}

std::vector<int> AdjacencyMatriceGraph::getNeighbours(int v)
{
	std::vector<int> res;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		if (matrix[v][i] == 1)
			res.push_back(i);
	}
	return res;
}

void AdjacencyMatriceGraph::show()
{
	std::cout << "Graf jako macierz sasiedztwa: " << std::endl;
	std::cout << "-\t";
	for (size_t i = 0; i < matrix.size(); i++)
		std::cout << i << "\t";
	std::cout << std::endl;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		std::cout << i << "\t";
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
// tworzy polaczenie skierowane 
bool AdjacencyMatriceGraph::addConnection(const std::pair<int, int>& c)
{
	if (matrix[c.first][c.second] != 0)
		return false;

	matrix[c.first][c.second] = 1;
	matrix[c.second][c.first] = -1;
	return true;
}

//dziala na polaczeniu skierowanym
std::vector<std::pair<int, int>> AdjacencyMatriceGraph::toList()
{
	std::vector<std::pair<int, int>> res;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] == 1)
				res.push_back(std::make_pair(i, j));
		}
	}
	return res;
}



AdjacencyListGraph::AdjacencyListGraph()
{

}
AdjacencyListGraph::AdjacencyListGraph(const std::vector<std::pair<int, int>>& eL, size_t V)
{
	elListo.resize(V);

	for (auto connection : eL)
	{
		elListo[connection.first].push_back(connection.second);
	}
}

AdjacencyListGraph::~AdjacencyListGraph()
{

}

std::vector<int> AdjacencyListGraph::getVertices()
{
	std::vector<int> res;
	for (size_t i = 0; i < elListo.size(); i++)
	{
		res.push_back(i);
	}
	return res;
}

std::vector<int> AdjacencyListGraph::getNeighbours(int v)
{
	return elListo[v];
}

void AdjacencyListGraph::show()
{
	std::cout << "Graf jak list sasiedztwa:" << std::endl;
	for (size_t i = 0; i < elListo.size(); i++)
	{
		std::cout << i << ":\t";
		for (size_t j = 0; j < elListo[i].size(); j++)
		{
			std::cout << elListo[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
