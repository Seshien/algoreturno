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
	auto G_prim = *this;
	std::vector<int> D;
	D.resize(G_prim.getSize());
	std::vector<int> S;
	auto v = G_prim.getEven();
	while (true)
	{
		S.push_back(v);
		auto n = G_prim.getNeighbours(v);
		if (n.size() == 0)
			return S;
		auto u = n[0];
		std::fill(D.begin(), D.end(), 0);
		auto cv = 1;
		G_prim.DFSb(v, -1, D, cv);
		int i = 0;
		while (i < n.size() && matrix[v][u] == 2)
			u = n[i++];
		G_prim.removeConnection({ v, u });
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

DirectedGraf::DirectedGraf()
{
}

DirectedGraf::DirectedGraf(const std::vector<std::pair<int, int>>& eL, size_t V)
{
	this->init(eL, V);
}

DirectedGraf::~DirectedGraf()
{
}

void DirectedGraf::init(const std::vector<std::pair<int, int>>& eL, size_t V)
{
	elListo.resize(V);

	for (auto connection : eL)
	{
		elListo[connection.first].push_back(connection.second);
	}
}

std::vector<int> DirectedGraf::flores()
{
	auto res = std::vector<int>();
	auto S = std::stack<int>();
	auto G_prim = *this;
	
	auto v = G_prim.getEven();
	res.push_back(v);
	while(true)
	{
		while (G_prim.getNeighbours(v).size() != 0)
		{
			auto w = G_prim.getNeighbours(v)[0];
			S.push(v);
			G_prim.removeConnection({ v,w });
			v = w;
		}
		if (S.size() != 0)
		{
			v = S.top();
			S.pop();
			res.push_back(v);
		}
		else
		{
			std::reverse(res.begin(), res.end());
			return res;
		}
	}
}

void DirectedGraf::show()
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

bool DirectedGraf::addConnection(const std::pair<int, int>& c)
{
	for (size_t i = 0; i < elListo[c.first].size(); i++)
	{
		if (elListo[c.first][i] == c.second)
		{
			return false;
		}
	}
	elListo[c.first].push_back(c.second);
}

bool DirectedGraf::removeConnection(const std::pair<int, int>& c)
{
	for (size_t i = 0; i < elListo[c.first].size(); i++)
	{
		if (elListo[c.first][i] == c.second)
		{
			elListo[c.first].erase(elListo[c.first].begin() + i);
			return true;
		}
	}
	return false;
}

int DirectedGraf::getSize() const
{
	return elListo.size();
}

std::vector<int> DirectedGraf::getVertices()
{
	std::vector<int> res;
	for (size_t i = 0; i < elListo.size(); i++)
	{
		res.push_back(i);
	}
	return res;
}

std::vector<int> DirectedGraf::getNeighbours(int v)
{
	return elListo[v];
}

int DirectedGraf::getEven()
{
	for (size_t i = 0; i < elListo.size(); i++)
	{
		if (elListo[i].size() != 0 && elListo[i].size() % 2 == 0)
			return i;
	};
	return -1;
}

