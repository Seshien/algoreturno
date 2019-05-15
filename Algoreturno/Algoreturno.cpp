#include "pch.h"
#include <iostream>
void fulltest()
{
	std::map<int, std::vector<std::vector<std::pair<int, int>>>> grafs;
	GenGraf graf;
	std::cout << "Start of graf generating" << std::endl;
	std::vector<int> val{ 10,50,100,150,300,500,1000,2000,3000,5000,7000,10000 };
	std::vector<int> val2{ 10,20,30,40,50,60,70,80,90 };
	for (auto x : val)
	{
		std::cout << "Generating 10 grafs with " << x << " vertexes" << std::endl;
		size_t i = 0;
		for (auto y : val2)
			while (i < 10)
			{
				graf.simplifiedGen(x, y);
				grafs[x].push_back(graf.retGraf());
			}
	}
	std::cout << "Testy:" << std::endl;
	for (auto x : val)
	{
		std::ofstream file("test_v2_" + std::to_string(x) + ".txt", std::ios::out);
		std::vector< AdjacencyMatriceGraph> macierzeSasiedztwa;
		std::vector< AdjacencyListGraph> listyNastepnikow;
		std::vector< EdgeListGraph > listyKrawedzi;
		for (size_t i = 0; i < 10; i++)
		{
			macierzeSasiedztwa.push_back({ grafs[x][i], (size_t)x });
			listyNastepnikow.push_back({ grafs[x][i], (size_t)x });
			listyKrawedzi.push_back({ grafs[x][i], (size_t)x });
		}
		std::cout << "Test 10 macierzy o " << x << " wierzcholkach dla macierzy sasiedztwa DFS" << std::endl;
		auto start = std::chrono::system_clock::now();
		for (size_t i = 0; i < 10; i++)
		{
			macierzeSasiedztwa[i].DFS_TopologicalSorting(false);
		}
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::cout << "Czas trwania: " << elapsed_seconds.count() << "s\n";
		file << "Macierz_sasiedztwa_DFS: " << elapsed_seconds.count() << std::endl;

		std::cout << "Test 10 macierzy o " << x << " wierzcholkach dla macierzy sasiedztwa DEL" << std::endl;
		start = std::chrono::system_clock::now();
		for (size_t i = 0; i < 10; i++)
		{
			macierzeSasiedztwa[i].DEL_TopologicalSorting(false);
		}
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		std::cout << "Czas trwania: " << elapsed_seconds.count() << "s\n";
		file << "Macierz_sasiedztwa_DEL: " << elapsed_seconds.count() << std::endl;

		std::cout << "Test 10 macierzy o " << x << " wierzcholkach dla listy nastepnikow DFS" << std::endl;
		start = std::chrono::system_clock::now();
		for (size_t i = 0; i < 10; i++)
		{
			listyNastepnikow[i].DFS_TopologicalSorting(false);
		}
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		std::cout << "Czas trwania: " << elapsed_seconds.count() << "s\n";
		file << "Listy_nastepnikow_DFS: " << elapsed_seconds.count() << std::endl;

		std::cout << "Test 10 macierzy o " << x << " wierzcholkach dla listy nastepnikow DEL" << std::endl;
		start = std::chrono::system_clock::now();
		for (size_t i = 0; i < 10; i++)
		{
			listyNastepnikow[i].DEL_TopologicalSorting(false);
		}
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		std::cout << "Czas trwania: " << elapsed_seconds.count() << "s\n";
		file << "Listy_nastepnikow_DEL: " << elapsed_seconds.count() << std::endl;

		std::cout << "Test 10 macierzy o " << x << " wierzcholkach dla listy krawedzi DFS" << std::endl;
		start = std::chrono::system_clock::now();
		for (size_t i = 0; i < 10; i++)
		{
			listyKrawedzi[i].DFS_TopologicalSorting(false);
		}
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		std::cout << "Czas trwania: " << elapsed_seconds.count() << "s\n";
		file << "Listy_krawedzi_DFS: " << elapsed_seconds.count() << std::endl;

		std::cout << "Test 10 macierzy o " << x << " wierzcholkach dla listy krawedzi DEL" << std::endl;
		start = std::chrono::system_clock::now();
		for (size_t i = 0; i < 10; i++)
		{
			listyKrawedzi[i].DEL_TopologicalSorting(false);
		}
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		std::cout << "Czas trwania: " << elapsed_seconds.count() << "s\n";
		file << "Listy_krawedzi_DEL: " << elapsed_seconds.count() << std::endl;

		file.close();

	}

}
int main()
{
	std::cout << "Witamy w programie symulujacym grafy." << std::endl;
	GenGraf graf;
	size_t number=0,number2=0;
	char choice = 'c';
	while (choice != 'e')
	{
		while (graf.ifEmpty())
		{
			std::cout << "Musisz utworzyc graf na ktorym chcesz pracowac. Czy chcesz uzyc generatora?[y/n]" << std::endl;
			std::cin >> choice;
			if (choice == 'y')
			{
				std::cout << "Prosze podac ilosc wierzcholkow oraz procent krawedzi." << std::endl;

				std::cin >> number >> number2;
				graf.simplifiedGen(number, number2);
			}
			else
			{
				std::cout << "Czy chcesz wczytac dane z pliku?[y/n]" << std::endl;
				std::cin >> choice;
				if (choice == 'y')
				{
					graf.loadGraf(number);
					if (graf.ifEmpty())
						std::cout << "Wystapil blad, graf nie zostal wczytany." << std::endl;
					else
						graf.showEdges();
				}
				else
					graf.manualGraf(number);
			}
		}


		//nieskierowany
		UndirectedGraf macierzSasiedztwa{ graf.retGraf(), number };
		//skierowany
		DirectedGraf listaNastepnikow{ graf.retGraf(), number };

		while (!(graf.ifEmpty()))
		{
			std::cout << "<-------------------------------------------------------------->" << std::endl;
			std::cout << "Graf istnieje. Wybierz czynnosc z listy." << std::endl;
			std::cout << "<-------------------------------------------------------------->" << std::endl;
			std::cout << "Pokaz graf: Jako macierz sasiedztwa[M], jako liste nastepnikow[N]." << std::endl;
			std::cout << "Cykl Eulera nieskierowany[c]. Cykl Eulera skierowany[C]. Cykl Hamiltona nieskierowany [h]. Cykl Hamiltona skierowany[H]." << std::endl;
			std::cout << "Usuwanie grafu[u]. Wyjdz z programu[e]." << std::endl;
			std::cin >> choice;
			switch (choice)
			{
			case 'M':
				macierzSasiedztwa.show();
				break;
			case 'N':
				listaNastepnikow.show();
				break;
			case 'e':
				std::cout << "Wychodzenie z programu." << std::endl;
				graf.clearGraf();
				break;
			case 'u':
				std::cout << "Usuwanie grafu." << std::endl;
				graf.clearGraf();
				break;
			case 'h':
				std::cout << "Cykl Hamiltona:" << std::endl;
				for (auto x : macierzSasiedztwa.roberts())
				{
					std::cout << " " << x;
				}
				std::cout << std::endl;
				break;
			case 'H':
				std::cout << "Cykl Hamiltona:" << std::endl;
				for (auto x : listaNastepnikow.roberts())
				{
					std::cout << " " << x;
				}
				std::cout << std::endl;
				break;
			case 'c':
				std::cout << "Cykl Eulera: " << std::endl;
				for (auto x: macierzSasiedztwa.flores())
				{
					std::cout << " " << x;
				}
				std::cout << std::endl;
				break;
			case 'C':
				std::cout << "Cykl Eulera: " << std::endl;
				for (auto x : listaNastepnikow.flores())
				{
					std::cout << " " << x;
				}
				std::cout << std::endl;
				break;
			default:
				std::cout << "Komenda nie rozpoznana." << std::endl;
			}
			std::cout << "<-------------------------------------------------------------->" << std::endl;
		}
	}
}
