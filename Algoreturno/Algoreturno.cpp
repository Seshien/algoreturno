#include "pch.h"

void fulltest()
{
	std::vector<double> times;

	double odchylenie;
	size_t i = 0;
	int j = 0;
	double ave = 0;
	GenGraf graf;
	std::cout << "Start of graf generating" << std::endl;
	std::vector<size_t> val;
	std::vector<size_t> val2{ 10,20,30,40,50,60,70,80,90 };
	int val3;
	for (size_t k = 5; k <= 30; k++)
		val.push_back(k);
	for (auto test : val)
		for (auto test2 : val2)
		{
			std::cout << "Ilosc wierzcholkow: " << test << " Nasycenie: " << test2 <<" Krawedzie: "<< (test * (test - 1)) / (2 * 100.0 / test2) <<std::endl;
		}
	std::string names[] = { "Undirected_roberts.txt","Directed_roberts.txt","Undirected_flores.txt","Directed_flores.txt" };
	std::ofstream plik, plikt;
	std::vector<int> temp;
	for (int i = 0; i < 4; i++)
	{
		plik.open(names[i], std::ios::out);
		plik << "Wierzcholki:Nasycenie:Czas:Odchylenie" << std::endl;
		plik.close();
	}
	for (auto x : val)
	{
		for (int k = 2; k < 4; k++)
		{
			plik.open(names[k], std::ios::app);
			plikt.open("templog.txt", std::ios::app);
			plikt << names[k] << std::endl;
			std::cout << "Generating grafs with " << x << " vertexes." << std::endl;
			for (auto y : val2)
			{
				i = 0;
				j = 0;
				val3 = (x * (x - 1)) / (2 * 100.0 / y);
				//if ((val3 % 2 == 0 || x > val3) && k>1)
				//{
				//	i = 10;
				//}
				std::cout << "Generating grafs with " << y << " percent of connections." << std::endl;
				std::cout << "Using " << names[k] << " algorithm." << std::endl;
				while (i < 10)
				{
					graf.simplifiedGen(x, y);
					UndirectedGraf *grafu = new UndirectedGraf{ graf.retGraf(),x };
					DirectedGraf *grafd = new DirectedGraf{ graf.retGraf(), x };
					auto start = std::chrono::system_clock::now();
					switch (k)
					{
					case 0:
						temp=grafu->roberts();
						break;
					case 1:
						temp=grafd->roberts();
						break;
					case 2:
						temp=grafu->flores();
						break;
					case 3:
						temp=grafd->flores();
						break;
					}
					auto end = std::chrono::system_clock::now();
					std::chrono::duration<double> elapsed_seconds = end - start;
					delete grafu;
					delete grafd;
					if (!(temp.empty()))
					{
						std::cout << "Cykl znaleziony" << std::endl;
						times.push_back(elapsed_seconds.count());
						i++;
					}
					else
						j++;
					if (k < 2)
					{
						if (j > (i + 1) * 10000)
						{
							std::cout << "Cykl NIEznaleziony" << std::endl;
							break;
						}
					}
					else
					{
						if (j > (i + 1) * 1000000)
						{
							std::cout << "Cykl NIEznaleziony" << std::endl;
							break;
						}
					}
				}
				if (i == 0)
				{
					plik << x << ":" << y << ":" << -1 << ":" << -1 << std::endl;
					continue;
				}
				ave = 0;
				odchylenie = 0;
				for (auto z : times)
				{
					ave += z;
				}
				ave /= times.size();
				for (auto z : times)
					odchylenie += (ave - z)*(ave - z);
				odchylenie = sqrt(odchylenie / times.size() * 1.0);
				plik << x << ":" << y << ":" << ave << ":" << odchylenie << std::endl;
				plikt << x << ":" << y << ":" << ave << ":" << odchylenie << std::endl;
			}
			plikt.close();
			plik.close();
		}

	}
}
int main()
{
	std::srand(time(NULL));
	std::cout << "Witamy w programie symulujacym grafy." << std::endl;
	GenGraf graf;
	size_t number=0,number2=0;
	char choice = 'c';
	std::cout << "Full test? [?/n]" << std::endl;
	std::cin >> choice;
	if (choice != 'n')
		fulltest();
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
