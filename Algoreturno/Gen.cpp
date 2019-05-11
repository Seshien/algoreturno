#include "pch.h"

bool createR(std::vector<std::pair<int, int>> & relations, size_t nodes, bool cyclesearch)
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
		relations.push_back(std::make_pair(node1, node2));
		//AdjacencyListGraph listaNastepnikow{ relations, nodes };

		if (multiSearch(relations))
		{
			relations.pop_back();
			continue;
		}
		/*
		if (cyclesearch)
			if (listaNastepnikow.DFS_TopologicalSorting(false).empty())
			{
				relations.pop_back();
				continue;
			}
		*/
		check = 0;
	}
	return 0;
}

bool createN(std::vector<std::pair<int, int>> & relations, int node1, int node2, bool cyclesearch)
{
	if (node1 == node2)
	{
		std::cout << "Nie mozna stworzyc takiej relacji" << std::endl;
		return 1;
	}
	relations.push_back(std::make_pair(node1, node2));
	return 0;
}

std::vector<std::pair<int, int>> simplifiedGen(int n,int sat)
{
	std::srand(time(NULL));
	AdjacencyMatriceGraph g({}, n);
	size_t i = 0;
	while (i < n * (n - 1) / (2 * 100 / sat))
	{
		int a = std::rand() % n;
		int b = (std::rand() % (n - a)) + a;
		if (a != b)
			if (g.addConnection(std::make_pair(a, b)))
				i++;
	}

	auto res = g.toList();
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

	for (size_t i = 0; i < res.size(); i++)
	{
		res[i].first = swapVector[res[i].first];
		res[i].second = swapVector[res[i].second];

	}

	return res;
}

bool multiSearch(const std::vector<std::pair<int, int>> & relations)
{
	for (int i = 0; i < relations.size(); i++)
		for (int j = 0; j < relations.size(); j++)
		{
			if (i == j)
				continue;
			if (relations[j] == relations[i])
				return 1;
			if ((relations[j].first == relations[i].second) && (relations[j].second == relations[i].first))
				return 1;
		}
	return 0;
}
std::vector<std::pair<int, int>> loadGraf(size_t & number)
{
	std::vector<std::pair<int, int>> graf;
	std::ifstream plik;
	std::string filename;
	std::cout << "Prosze podac nazwe pliku" << std::endl;
	std::cin >> filename;
	plik.open(filename, std::ifstream::in);
	if (plik.good() == 0)
	{
		std::cout << "Nie uzyskano dostepu do pliku." << std::endl;
		return graf;
	}
	else
		std::cout << "Dostêp zosta³ uzyskany." << std::endl;
	int n, v, node1, node2;
	char choice;
	bool cycle = true;
	plik >> n >> v;
	number = n;
	for (int i = 0; i < v; i++)
	{
		plik >> node1 >> node2;
		if (createN(graf, node1, node2))
		{
			std::cout << "Wystapil blad podczas dodawania krawedzi do grafu" << std::endl;
		}
	}
	return graf;
}

std::vector<std::pair<int, int>> manualGraf(size_t & number)
{
	int num1 = 1, num2 = 2;
	std::vector<std::pair<int, int>> graph;
	std::cout << "Podaj liczbe wierzcholkow." << std::endl;
	std::cin >> number;
	while (1)
	{
		std::cout << "Podaj relacje. By zakonczyc, podaj dwie te same liczby." << std::endl;
		std::cin >> num1 >> num2;
		if (num1 == num2)
			break;
		if (createN(graph, num1, num2))
			std::cout << "Wystapil blad, relacja nie zostala dodana" << std::endl;
	}
	return graph;
}

std::vector<std::pair<int, int>> genGraf(int amount, int sat)
{
	std::srand(time(NULL));
	std::vector<std::pair<int, int>> relations;
	int sizeR = amount * (amount - 1) / (2 * 100 / sat);
	size_t amountt = amount;
	int i = 0;
	while (i < sizeR)
	{
		if (createR(relations, amountt))
		{
			i = 0;
			relations.clear();
		}
		else
			i++;
		//std::cout << "Relacja " << i << " stworzona. Pozostala ilosc: " << sizeR - i << std::endl;
	}
	showEdges(relations);
	std::cout << "Tworzenie gotowe" << std::endl;
	return relations;
}

void showEdges(const std::vector<std::pair<int, int>> & relations)
{
	for (auto i : relations)
		std::cout << "Relacja " << i.first << " : " << i.second << std::endl;
	std::cout << "Ilosc krawedzi grafu: " << relations.size() << std::endl;
}