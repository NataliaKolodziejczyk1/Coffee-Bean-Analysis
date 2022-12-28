#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <map> 
#include <iomanip>
#include "Country.h"
#include "Roast.h"

//#define TEST
using namespace std;


int main()
{

	/*
	WST�P
	Plik kt�ry analizujemy jest bardzo d�ugi i posiada wiele danych. Chcemy si� dowiedzie�, w jakim kraju ziarna kawy dostawa�y �rednio najwi�ksz� ocen�.
	W tym celu bedzi�my potrzebowa� kolumny Country.of.Origin - 4 kolumna oraz Total.Cup.Points - 31 kolumna. Spos�b post�powania b�dzie nast�puj�cy:
	W mapie countries b�dziemy przechowywa� nazwe kraju oraz obiekt klasy Country, kt�ry pomo�e nam w uporz�dkowaniu danych obliczeniu �redniej oceny.
	Natrafiaj�c na nazw� kraju b�dziemy sprawdza�, czy ju� znajduje si� taki kraj na naszej mapie. Je�li nie, dodajemy go i tworzymy obiekt Country.
	Nast�pnie w obu przypadkach do wektora ocen dopisujemy przeczytan� ocen�.

	Czytaj�c dane natrafiamy na pewien problem - dane s� rozdzielone przecinkiem, ale je�li przecinek wyst�puje wewn�trz " ", wtedy nie rozdziela kolumn
	a stanowi po prostu tre�� danego pola. Aby rozwi�za� ten problem za ka�dym razem przed przeczytaniem nast�pnego pola (Mamy pewno��, �e pierwsze pole nie
	zawiera , bo to po prostu liczba porz�dkowa) czytamy jeden znak. Je�li jest on r�wny " to koniec pola wyznacza ",. Czytamy wi�c dane a� do nast�pnego " i zjadamy
	nast�puj�cy po nim ,. W przeciwnym wypadku czytamy po prostu do nast�pnego przecinku.
	*/

	ifstream in{"merged_data_cleaned.csv"}; //otwieramy pierwszy plik
	//ifstream in{"test.csv"}; //plik do test�w
	string s; //bedziemy tu wczytywa� wiersze 
	string word; //do przechowywania s��w
	vector<string> line; //do przechowania poszczeg�lnych kolumn z wiersza
	
	unordered_map<string,Country> countries; // bedziemy tu przechowywa� nazwe kraju oraz obiekt Country dla danego kraju
	string name; // zmienna pomocnicza do nazwy kraju
	double rating; //zmienna pomocnicza do oceny ziaren


	getline(in,s); //pierwszy wiersz jest nag�owkiem, wi�c go pomijamy
	
	while(getline(in,s)) //czytamy po kolei linie
	{
		line.clear(); // czy�cimy wektor
		stringstream str(s); //otwieramy strumie� string�w
		
		while(getline(str,word,',')) // dane rozdziela przecinek, wi�c czytamy po kolei pola
		{
			line.push_back(word); // dan� kolumne wrzucamy do wektora dla danej linii

			while(str.get() == '"') //rozwi�zujemy problem z "" opisany we wst�pie
			{
				// je�li tu weszli�my, to oznacza �e trafili�my na kolumn� zawart� w " "
				getline(str,word,'"');
				line.push_back(word);
				str.get(); // zjadamy pozosta�y przecinek
			}
			str.unget(); // po wyj�ciu z p�tli musimy zwr�ci� znak kt�ry zjedli�my
		
			
		}

			name = line[3]; // wpisujemy nazw� kraju do zmiennej pomocniczej
			if(countries.find(name) == countries.end()) //sprawdzamy, czy dany kraj jest ju� na naszej mapie
			{
				countries[name] = Country(name); //je�li nie, dopisujemy go do naszej mapy i tworzymy dla niego obiekt Country
			}

			try // funkcja stod musi by� zawarta w try catch bloku, powniewa� inaczej generuje b��dy...
			{
				rating = stod(line[30]); // przekonwertowanie string na double
				countries[name].Add_cup_points(rating); // u�ywamy metody klasy by dopisa� do wektora dla danego kraju ocen�
			}
			catch(...)
			{
			}
	}

#ifdef TEST
	for(auto pair : countries)
	{
		cout << pair.first << endl;
	}
	countries["Haiti"].Print_vector();
	cout <<"Haiti average rating: " << countries["Haiti"].Average_rating() << endl;
#endif
	map<double,string> Ratings; // tworzymy zwyk�� map� �rednich ocen dla danego kraju - przy wypisywaniu oceny bed� od razu uporz�dkowane

	for(auto i : countries)
	{
		Ratings[i.second.Average_rating()] = i.first; //Dla ka�dego kraju wyliczamy �redni� 
	}

	for(map<double,string>::iterator i = Ratings.end(); i != Ratings.begin();) // teraz wypisujemy potrzebne dane
	{
		//w ka�dym wierszy wypisujemy nazw� kraju, �redni� ocen� oraz liczb� ocen
		i--;
		cout << left << setw(30) << i->second << " average cup points: " << setw(15) << i->first;
		cout << "Number of ratings: " << countries[i->second].Number_of_ratings() << endl;
	}
	cout << "\n\n";
	/*
	WNIOSKI
	Widzimy, �e na pierwszym miejscu w naszym rankingu jest Papua Nowa Gwinea, ale tylko z jedn� ocen�. Drugie miejsce zajmuje Etiopia z ju� 44 ocenami,
	czyli wysokie miejsce wydaje si� tu by� bardziej uzasadnione ni� w przypadku Nowej Gwinei. 3 miejsce zajmuje Japonia, r�wnie� z tylko jedn� ocen�.
	*/

	//------------------------------------------------------------------------------------------------------------------------------------------------------//


	/*
	WST�P
	Teraz chcemy odpowiedzie� na nast�pne pytanie jaki wp�yw ma stopie� palenia ziaren na aromat, kwasowo��, smak i posmak kawy? Potrzebujemy nast�puj�cych kolumn z 
	pliku coffee_df: 3 kolumna roast, 7 kolumna aroma, 8 kolumna acid, 10 kolumna flavor, 11 kolumna aftertaste. W mapie roasts b�dziemy przechowywa� stopnie palenia
	kawy i dla ka�dego stopnia odpowiadaj�cy mu obiekt klasy Roast zawieraj�cy wektory dla parametr�w kawy. Natrafiaj�c na nowy stopie� palenia kawy b�dziemy
	dodawa� go do mapy i tworzy� dla niego nowy obiekt Roast. Na koniec policzymy dla powsta�ych obiekt�w ilo�� danych, �rednie, mediany oraz odchylenia standardowe,
	kt�re b�dzie nam m�wi� jak bardzo dane s� rozrzucone wok� �redniej.

	W tym pliku wyst�powa� podobny problem z przecinkami co w pliku pierwszym, spos�b post�powania jest analogiczny. Tylko cudzys�owia pojawij� si� w dw�ch pierwszych
	kolumnach, wi�c tutaj b�dziemy zaczyna� od p�tli wczytuj�cej kolumny z " " w razie ich wyst�pienia. Dodatkowo wprowadzamy zmienn� licz�c� wczytane kolumny,
	aby m�c przerwa� czytanie danych po zdobyciu wszystkich potrzebnych danych
	*/
	
	in.close();
	in.open("coffee_df.csv"); //otwieramy drugi plik


	unordered_map<string,Roast> roasts; // b�dziemy tu zawiera� stopieN palenia kawy oraz obiekt typu Roast przechowuj�cy dane danego stopnia palenia
	string roast_type; // zmienne pomocnicze do przechowywania danych
	int aroma;
	int acid;
	int flavor;
	int aftertaste;

	getline(in,s); //pierwszy wiersz jest nag�owkiem, wi�c go pomijamy

	// dane czytamy w identyczny spos�b jak poprzednio
	while(getline(in,s)) // czytamy wiersz z pliku
	{
		line.clear(); // czyscimy wektor 
		stringstream str(s); //otwieramy strumie� stringow
		
		while(str.get() == '"') //je�li kolumny maj� " ", wczytujemy je
		{
			getline(str,word,'"');
			line.push_back(word);
			str.get();
		}
		str.unget();

		while(getline(str,word,','))
		{
			line.push_back(word);
			while(str.get() == '"') //je�li kolumny maj� " ", wczytujemy je
			{
				getline(str,word,'"');
				line.push_back(word);
				str.get();
			}
			str.unget();
		}

		roast_type = line[2]; // wpisujemy stopie� palenia kawy do zmiennej pomocniczej
		if(roasts.find(roast_type) == roasts.end()) //sprawdzamy, czy dany stopie� palenia jest ju� w mapie
		{
			roasts[roast_type] = Roast(roast_type); //je�li nie, dopisujemy go do naszej mapy i tworzymy dla niego obiekt Roast
		}

		try // funkcja stod musi by� zawarta w try catch bloku, powniewa� inaczej generuje b��dy...
		{
			aroma = stoi(line[6]); // przypisujemy warto�ci z wektora do zmiennych pomocniczych
			acid = stoi(line[7]);
			flavor = stoi(line[9]);
			aftertaste = stoi(line[10]);
			roasts[roast_type].Add_aroma(aroma); // wpisujemy warto�ci do wektor�w metodami klasy
			roasts[roast_type].Add_acid(acid);
			roasts[roast_type].Add_flavor(flavor);
			roasts[roast_type].Add_aftertaste(aftertaste);
		}
		catch(...)
		{
		}
	}
#ifdef TEST
	for(auto pair : roasts)
	{
		cout << pair.first << endl;
		pair.second.Print_vector();
	}
	cout << '\n';
#endif
	for(auto pair : roasts) // dla ka�dego stopnia palenia wypisujemy podsumowanie w formie ramki z danymi
	{
		cout << "--------------------------------------------------------------------------------\n";
		cout << "Roast type: " << setw(68) << pair.first << "|" <<endl; // typ palenia
		cout << setw(20) << "Aroma:" << setw(20) << "Acid:" << setw(20) << "Flavor:" << setw(20) << "Aftertaste" << "|" << endl; // nag��wek
		cout << setw(10) << "Amount: " << setw(10) << pair.second.Size_of_vector(1); // liczba pomiar�w 
		cout << setw(10) << "Amount: " << setw(10) << pair.second.Size_of_vector(2);
		cout << setw(10) << "Amount: " << setw(10) << pair.second.Size_of_vector(3);
		cout << setw(10) << "Amount: " << setw(10) << pair.second.Size_of_vector(4) << "|\n";
		cout << setw(10) << "Average: " << setw(10) << pair.second.Average(1); // �rednie 
		cout << setw(10) << "Average: " << setw(10) << pair.second.Average(2);
		cout << setw(10) << "Average: " << setw(10) << pair.second.Average(3);
		cout << setw(10) << "Average: " << setw(10) << pair.second.Average(4) << "|\n";
		cout << setw(10) << "Median: " << setw(10) << pair.second.Median(1); //mediany
		cout << setw(10) << "Median: " << setw(10) << pair.second.Median(2);
		cout << setw(10) << "Median: " << setw(10) << pair.second.Median(3);
		cout << setw(10) << "Median: " << setw(10) << pair.second.Median(4) << "|\n";
		cout << setw(10) << "Std dev: " << setw(10) << pair.second.Standard_Deviation(1); // odchylenie standardowe
		cout << setw(10) << "Std dev: " << setw(10) << pair.second.Standard_Deviation(2);
		cout << setw(10) << "Std dev: " << setw(10) << pair.second.Standard_Deviation(3);
		cout << setw(10) << "Std dev: " << setw(10) << pair.second.Standard_Deviation(4) << "|\n";
		cout << "--------------------------------------------------------------------------------\n";
		cout << "\n\n";
	}
	/*
	WNIOSKI
	Dla lekkiego stopnia palenia charakterystyczna jest najwi�ksza kwasowo�� wynosz�ca �rednio 8.57452. Aromat, smak i posmak takich ziaren jest �rednio nieco mniejszy, ni� dla ziaren Medium-Light. Dla tego typu najbardziej charakterystyczny jest smak kawy,
	wynosz�cy �rednio 8.99856, odchylenie standardowe tej warto�ci wynosi zaldwie 0.294135, co oznacza, �e wszystkie warto�ci odbiegaj� od �redniej warto�ci tylko w niewielkim stopniu. Dla innych rodzaj�w ziaren mamy ju� du�o mniej pr�bek, ale te�
	mo�emy z nich wyci�gn�� pewne wnioski. Widzimy, �e od stopnia palenia Medium im bardziej s� pra�one ziarna, tym bardziej malej� wszystkie z ich parametr�w. Dla �redniego stopnia palenia najwi�kszy spadek nast�pi� dla kwasowo�ci, wynosi ona zaledwie 8.15054.
	Dla Medium-Dark aromat, kwasowo�� i posmak zmala�y o oko�o 0.5. Dla ziaren Dark kwasowo�� i posmak spad�y poni�ej 7, jedynym wzgl�dnie wysokim parametrem pozostaje dla tych ziaren smak z �redni� 8.
	*/

	//------------------------------------------------------------------------------------------------------------------------------------------------------//

	/*
	WST�P
	Ostatnie zadanie tego programu, to znalezienie najbli�szej kawiarni Starbuck do podanej przez u�ytkowanika lokalizacji (d�ugo�ci oraz szeroko�ci geograficznej). Do tego celu potrzebujemy z pliku directory.csv nast�puj�cych kolumn: 12 - Longitude, 13 - Latitude oraz
	kolumny 3 - Store Name, 5 - Street Address oraz 6 - City do zwr�cenia u�ytkownikowi informacji o znalezionym przez program lokalu.
	*/

	in.close();
	in.open("directory.csv"); //otwieramy trzeci plik

	double longitude; // zmienne pomocnicze
	double latitude;
	double min_dist = 1000000; // poczatkowy dystans ma by� teoretycznie niesko�czono�ci�, ale mo�emy tu wstawi� po prostu jakas du�� liczb�
	double curr_dist;
	string store_name;
	string street;
	string city;

	cout << "Podaj dlugosc geograficzna: ";
	cin >> longitude;
	cout << '\n';
	cout << "Podaj szerokosc geograficzna: ";
	cin >> latitude;
	cout << '\n';

	getline(in,s); //pierwszy wiersz jest nag�owkiem, wi�c go pomijamy

	while(getline(in,s)) //czytamy po kolei linie
	{
		line.clear(); // czy�cimy wektor
		stringstream str(s); //otwieramy strumie� string�w

		while(getline(str,word,',')) // dane rozdziela przecinek, wi�c czytamy po kolei pola
		{
			line.push_back(word); // dan� kolumne wrzucamy do wektora dla danej linii

			while(str.get() == '"') //rozwi�zujemy problem z "" opisany we wst�pie
			{
				// je�li tu weszli�my, to oznacza �e trafili�my na kolumn� zawart� w " "
				getline(str,word,'"');
				line.push_back(word);
				str.get(); // zjadamy pozosta�y przecinek
			}
			str.unget(); // po wyj�ciu z p�tli musimy zwr�ci� znak kt�ry zjedli�my
		}

		try // funkcja stod musi by� zawarta w try catch bloku
		{
			if(line.size() == 13) // sprawdzamy, czy na pewno linia kt�r� wczytali�my jest kompletna
			{
				curr_dist = sqrt(pow(longitude-stod(line[11]),2) + pow(latitude-stod(line[12]),2)); // liczymy odleg�o�� mi�dzy dwoma punktami na mapie
				if(curr_dist < min_dist) // je�li aktualna odleg�o�� jest mniejsza ni� aktualnie zapisana odleg�o�� minimalna to oznacza, �e znale�li�my jeszcze bli�szy sklep
				{
					min_dist = curr_dist;
					store_name = line[2];
					street = line[4];
					city = line[5];
				}
			}
		}
		catch(...)
		{
		}
	}
	cout << "Najblizszy ciebie Starbucks to: " << store_name << '\n' << "O adresie: " << street << ", " << city << endl;
}

