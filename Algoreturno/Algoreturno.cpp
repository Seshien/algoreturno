#include "pch.h"
#include <iostream>

int main()
{
	std::cout << "Witamy w programie symulujacym grafy." << std::endl;
	std::vector<std::pair<int, int>> graf;
	size_t number,number2;
	char choice = 'c';
	while (choice != 'e')
	{
		while (graf.empty())
		{
			std::cout << "Musisz utworzyc graf na ktorym chcesz pracowac. Czy chcesz uzyc generatora?[y/n]" << std::endl;
			std::cin >> choice;
			if (choice == 'y')
			{
				std::cout << "Prosze podac ilosc wierzcholkow oraz procent wierzcholkow." << std::endl;
				std::cin >> number >> number2;
				//graf = simplifiedGen(number, number2);
			}
			else
			{
				std::cout << "Czy chcesz wczytac dane z pliku?[y/n]" << std::endl;
				std::cin >> choice;
				if (choice == 'y')
				{
					graf = loadGraf(number);
					if (graf.empty())
						std::cout << "Wystapil blad, graf nie zostal wczytany." << std::endl;
					else
						showEdges(graf);
				}
				else
					graf = manualGraf(number);
			}
		}


		//nieskierowany
		UndirectedGraf macierzSasiedztwa{ graf, number };
		//skierowany
		AdjacencyListGraph listaNastepnikow{ graf, number };

		while (!(graf.empty()))
		{
			std::cout << "<-------------------------------------------------------------->" << std::endl;
			std::cout << "Graf istnieje. Wybierz czynnosc z listy." << std::endl;
			std::cout << "<-------------------------------------------------------------->" << std::endl;
			std::cout << "Pokaz graf: Jako macierz sasiedztwa[M], jako liste nastepnikow[N]." << std::endl;
			std::cout << "Usuwanie grafu[u]. Cykl Eulera[c] Wyjdz z programu[e]." << std::endl;
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
				graf.clear();
				break;
			case 'u':
				std::cout << "Usuwanie grafu." << std::endl;
				graf.clear();
				break;
			case 'c':
				std::cout << "Cykl Eulera: " << std::endl;
				for (auto x: macierzSasiedztwa.flores())
				{
					std::cout << " " << x;
				}
				std::cout << std::endl;
				macierzSasiedztwa.init(graf, number);
				break;
			default:
				std::cout << "Komenda nie rozpoznana." << std::endl;
			}
			std::cout << "<-------------------------------------------------------------->" << std::endl;
		}
	}
}
