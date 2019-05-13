#include "pch.h"

GenGraf::GenGraf()
{

}

GenGraf:: ~GenGraf()
{

}

bool GenGraf::clearGraf()
{
	generated.clear();
	return 0;
}

bool GenGraf::ifEmpty()
{
	if (generated.empty())
		return 1;
	return 0;
}

std::vector<std::pair<int, int>> GenGraf::retGraf()
{
	return generated;
}

bool GenGraf::createR(size_t nodes)
{
	int node1, node2;
	int check = 1, failsafe = nodes * nodes*nodes;
	if (failsafe < 100) failsafe = 100;
	while (check > 0)
	{
		//std::cout << "DFS Check: " << check << std::endl;
		check++;
		if (check > failsafe) return 1;
		node1 = rand() % nodes;
		node2 = rand() % nodes;
		if (node1 == node2) continue;
		generated.push_back(std::make_pair(node1, node2));
		//AdjacencyListGraph listaNastepnikow{ relations, nodes };

		if (multiSearch())
		{
			generated.pop_back();
			continue;
		}
		check = 0;
	}
	return 0;
}

bool GenGraf::createN(int node1, int node2)
{
	if (node1 == node2)
	{
		std::cout << "Nie mozna stworzyc takiej relacji" << std::endl;
		return 1;
	}
	if (multiSearch())
	{
		generated.pop_back();
		std::cout << "Nie mozna stworzyc takiej relacji" << std::endl;
		return 1;
	}
	generated.push_back(std::make_pair(node1, node2));
	return 0;
}
 //Tworzy skierowany graf
bool GenGraf::simplifiedGen(int n,int sat)
{
	std::srand(time(NULL));
	std::vector<std::vector<int>> matrix;
	matrix.resize(n);
	for (auto &x : matrix)
	{
		x.resize(n);
	}
	size_t i = 0;
	while (i < n * (n - 1) / (2 * 100 / sat))
	{
		int a = std::rand() % n;
		int b = std::rand() % n;
		if (a != b)
			if (addConnection(matrix,std::make_pair(a, b)))
				i++;
	}

	generated = toList(matrix);
	std::vector<int> swapVector;
	for (size_t i = 0; i < n; i++)
	{
		int a;
		do
		{
			a = std::rand() % n;
		} while (std::find(std::begin(swapVector), std::end(swapVector), a) != swapVector.end());
		swapVector.push_back(a);
	}

	for (size_t i = 0; i < generated.size(); i++)
	{
		generated[i].first = swapVector[generated[i].first];
		generated[i].second = swapVector[generated[i].second];

	}
	//if (multiSearch())
	//	std::cout << "Multigraf" << std::endl;
	return 0;
}

bool GenGraf::multiSearch()
{
	for (int i = 0; i < generated.size(); i++)
		for (int j = 0; j < generated.size(); j++)
		{
			if (i == j)
				continue;
			if (generated[j] == generated[i])
				return 1;
			if ((generated[j].first == generated[i].second) && (generated[j].second == generated[i].first))
				return 1;
		}
	return 0;
}
bool GenGraf::loadGraf(size_t & number)
{
	clearGraf();
	std::ifstream plik;
	std::string filename;
	std::cout << "Prosze podac nazwe pliku" << std::endl;
	std::cin >> filename;
	plik.open(filename, std::ifstream::in);
	if (plik.good() == 0)
	{
		std::cout << "Nie uzyskano dostepu do pliku." << std::endl;
		return 1;
	}
	else
		std::cout << "Dostêp zosta³ uzyskany." << std::endl;
	int n, v, node1, node2;
	bool cycle = true;
	plik >> n >> v;
	number = n;
	for (int i = 0; i < v; i++)
	{
		plik >> node1 >> node2;
		if (createN(node1, node2))
		{
			std::cout << "Wystapil blad podczas dodawania krawedzi do grafu" << std::endl;
		}
	}
	return 0;
}

bool GenGraf::manualGraf(size_t & number)
{
	clearGraf();
	int num1 = 1, num2 = 2;
	std::cout << "Podaj liczbe wierzcholkow." << std::endl;
	std::cin >> number;
	while (1)
	{
		std::cout << "Podaj relacje. By zakonczyc, podaj dwie te same liczby." << std::endl;
		std::cin >> num1 >> num2;
		if (num1 == num2)
			break;
		if (createN(num1, num2))
			std::cout << "Wystapil blad, relacja nie zostala dodana" << std::endl;
	}
	return 0;
}

bool GenGraf::genGraf(int amount, int sat)
{
	clearGraf();
	std::srand(time(NULL));
	int sizeR = amount * (amount - 1) / (2 * 100 / sat);
	size_t amountt = amount;
	int i = 0;
	while (i < sizeR)
	{
		if (createR(amountt))
		{
			i = 0;
			generated.clear();
		}
		else
			i++;
		//std::cout << "Relacja " << i << " stworzona. Pozostala ilosc: " << sizeR - i << std::endl;
	}
	showEdges();
	std::cout << "Tworzenie gotowe" << std::endl;
	return 0;
}

void GenGraf::showEdges()
{
	for (auto i : generated)
		std::cout << "Relacja " << i.first << " : " << i.second << std::endl;
	std::cout << "Ilosc krawedzi grafu: " << generated.size() << std::endl;
}

bool GenGraf::addConnection(std::vector<std::vector<int>> & matrix,const std::pair<int, int>& c)
{
	if (matrix[c.first][c.second] != 0)
		return false;

	matrix[c.first][c.second] = 1;
	matrix[c.second][c.first] = -1;
	return true;
}

std::vector<std::pair<int, int>> GenGraf::toList(std::vector<std::vector<int>> & matrix)
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