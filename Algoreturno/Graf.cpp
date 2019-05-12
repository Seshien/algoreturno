#include "pch.h"
#include "Graf.h"


UndirectedGraf::UndirectedGraf()
{
}

UndirectedGraf::UndirectedGraf(const std::vector<std::pair<int, int>>& eL, size_t V)
{
	this->init(eL, V);
}


UndirectedGraf::~UndirectedGraf()
{
}

void UndirectedGraf::init(const std::vector<std::pair<int, int>>& eL, size_t V)
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

std::vector<int> UndirectedGraf::flores()
{
	std::vector<int> D;
	D.resize(this->getSize());
	std::vector<int> S;
	auto v = this->getEven();
	while (true)
	{
		S.push_back(v);
		auto n = this->getNeighbours(v);
		if (n.size() == 0)
			return S;
		auto u = n[0];
		std::fill(D.begin(), D.end(), 0);
		auto cv = 1;
		this->DFSb(v, -1, D, cv);
		int i = 0;
		while (i < n.size() && matrix[v][u] == 2)
			u = n[i++];
		this->removeConnection({ v, u });
		v = u;
	}
	
}

void UndirectedGraf::show()
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

bool UndirectedGraf::addConnection(const std::pair<int, int>& c)
{
	if (matrix[c.first][c.second] != 0)
		return false;

	matrix[c.first][c.second] = 1;
	matrix[c.second][c.first] = 1;
	return true;
}

bool UndirectedGraf::removeConnection(const std::pair<int, int>& c)
{
	if (matrix[c.first][c.second] == 0)
		return false;

	matrix[c.first][c.second] = 0;
	matrix[c.second][c.first] = 0;
	return true;

}

int UndirectedGraf::getSize() const
{
	return matrix.size();
}

std::vector<int> UndirectedGraf::getVertices()
{
	std::vector<int> res;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		res.push_back(i);
	}
	return res;
}

std::vector<int> UndirectedGraf::getNeighbours(int v)
{
	std::vector<int> res;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		if (matrix[v][i] != 0)
			res.push_back(i);
	}
	return res;
}

int UndirectedGraf::getEven()
{
	for (size_t i = 0; i < matrix.size(); i++)
	{
		int sum = 0;
		for (auto it = matrix[i].begin(); it != matrix[i].end(); ++it)
		{
			if(*it != 0)
			sum ++;
		}		
		if (sum != 0 && sum % 2 == 0)
			return i;
	};
	return -1;
}

int UndirectedGraf::DFSb(int v, int vf, std::vector<int>& D, int & cv)
{
	D[v] = cv;
	auto L = cv;
	cv++;
	for (auto u : this->getNeighbours(v))
	{
		if (u != vf)
		{
			if (D[u] == 0)
			{
				auto tmp = DFSb(u, v, D, cv);
				if (tmp < L)
					L = tmp;
			}
			else if (D[u] < L)
			{
				L = D[u];
			}
		}
	}
	if (vf > -1 && L == D[v])
		matrix[vf][v] = 2;
	return L;
}
