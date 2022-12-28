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
	WSTÊP
	Plik który analizujemy jest bardzo d³ugi i posiada wiele danych. Chcemy siê dowiedzieæ, w jakim kraju ziarna kawy dostawa³y œrednio najwiêksz¹ ocenê.
	W tym celu bedziêmy potrzebowaæ kolumny Country.of.Origin - 4 kolumna oraz Total.Cup.Points - 31 kolumna. Sposób postêpowania bêdzie nastêpuj¹cy:
	W mapie countries bêdziemy przechowywaæ nazwe kraju oraz obiekt klasy Country, który pomo¿e nam w uporz¹dkowaniu danych obliczeniu œredniej oceny.
	Natrafiaj¹c na nazwê kraju bêdziemy sprawdzaæ, czy ju¿ znajduje siê taki kraj na naszej mapie. Jeœli nie, dodajemy go i tworzymy obiekt Country.
	Nastêpnie w obu przypadkach do wektora ocen dopisujemy przeczytan¹ ocenê.

	Czytaj¹c dane natrafiamy na pewien problem - dane s¹ rozdzielone przecinkiem, ale jeœli przecinek wystêpuje wewn¹trz " ", wtedy nie rozdziela kolumn
	a stanowi po prostu treœæ danego pola. Aby rozwi¹zaæ ten problem za ka¿dym razem przed przeczytaniem nastêpnego pola (Mamy pewnoœæ, ¿e pierwsze pole nie
	zawiera , bo to po prostu liczba porz¹dkowa) czytamy jeden znak. Jeœli jest on równy " to koniec pola wyznacza ",. Czytamy wiêc dane a¿ do nastêpnego " i zjadamy
	nastêpuj¹cy po nim ,. W przeciwnym wypadku czytamy po prostu do nastêpnego przecinku.
	*/

	ifstream in{"merged_data_cleaned.csv"}; //otwieramy pierwszy plik
	//ifstream in{"test.csv"}; //plik do testów
	string s; //bedziemy tu wczytywaæ wiersze 
	string word; //do przechowywania s³ów
	vector<string> line; //do przechowania poszczególnych kolumn z wiersza
	
	unordered_map<string,Country> countries; // bedziemy tu przechowywaæ nazwe kraju oraz obiekt Country dla danego kraju
	string name; // zmienna pomocnicza do nazwy kraju
	double rating; //zmienna pomocnicza do oceny ziaren


	getline(in,s); //pierwszy wiersz jest nag³owkiem, wiêc go pomijamy
	
	while(getline(in,s)) //czytamy po kolei linie
	{
		line.clear(); // czyœcimy wektor
		stringstream str(s); //otwieramy strumieñ stringów
		
		while(getline(str,word,',')) // dane rozdziela przecinek, wiêc czytamy po kolei pola
		{
			line.push_back(word); // dan¹ kolumne wrzucamy do wektora dla danej linii

			while(str.get() == '"') //rozwi¹zujemy problem z "" opisany we wstêpie
			{
				// jeœli tu weszliœmy, to oznacza ¿e trafiliœmy na kolumnê zawart¹ w " "
				getline(str,word,'"');
				line.push_back(word);
				str.get(); // zjadamy pozosta³y przecinek
			}
			str.unget(); // po wyjœciu z pêtli musimy zwróciæ znak który zjedliœmy
		
			
		}

			name = line[3]; // wpisujemy nazwê kraju do zmiennej pomocniczej
			if(countries.find(name) == countries.end()) //sprawdzamy, czy dany kraj jest ju¿ na naszej mapie
			{
				countries[name] = Country(name); //jeœli nie, dopisujemy go do naszej mapy i tworzymy dla niego obiekt Country
			}

			try // funkcja stod musi byæ zawarta w try catch bloku, powniewa¿ inaczej generuje b³êdy...
			{
				rating = stod(line[30]); // przekonwertowanie string na double
				countries[name].Add_cup_points(rating); // u¿ywamy metody klasy by dopisaæ do wektora dla danego kraju ocenê
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
	map<double,string> Ratings; // tworzymy zwyk³¹ mapê œrednich ocen dla danego kraju - przy wypisywaniu oceny bed¹ od razu uporz¹dkowane

	for(auto i : countries)
	{
		Ratings[i.second.Average_rating()] = i.first; //Dla ka¿dego kraju wyliczamy œredni¹ 
	}

	for(map<double,string>::iterator i = Ratings.end(); i != Ratings.begin();) // teraz wypisujemy potrzebne dane
	{
		//w ka¿dym wierszy wypisujemy nazwê kraju, œredni¹ ocenê oraz liczbê ocen
		i--;
		cout << left << setw(30) << i->second << " average cup points: " << setw(15) << i->first;
		cout << "Number of ratings: " << countries[i->second].Number_of_ratings() << endl;
	}
	cout << "\n\n";
	/*
	WNIOSKI
	Widzimy, ¿e na pierwszym miejscu w naszym rankingu jest Papua Nowa Gwinea, ale tylko z jedn¹ ocen¹. Drugie miejsce zajmuje Etiopia z ju¿ 44 ocenami,
	czyli wysokie miejsce wydaje siê tu byæ bardziej uzasadnione ni¿ w przypadku Nowej Gwinei. 3 miejsce zajmuje Japonia, równie¿ z tylko jedn¹ ocen¹.
	*/

	//------------------------------------------------------------------------------------------------------------------------------------------------------//


	/*
	WSTÊP
	Teraz chcemy odpowiedzieæ na nastêpne pytanie jaki wp³yw ma stopieñ palenia ziaren na aromat, kwasowoœæ, smak i posmak kawy? Potrzebujemy nastêpuj¹cych kolumn z 
	pliku coffee_df: 3 kolumna roast, 7 kolumna aroma, 8 kolumna acid, 10 kolumna flavor, 11 kolumna aftertaste. W mapie roasts bêdziemy przechowywaæ stopnie palenia
	kawy i dla ka¿dego stopnia odpowiadaj¹cy mu obiekt klasy Roast zawieraj¹cy wektory dla parametrów kawy. Natrafiaj¹c na nowy stopieñ palenia kawy bêdziemy
	dodawaæ go do mapy i tworzyæ dla niego nowy obiekt Roast. Na koniec policzymy dla powsta³ych obiektów iloœæ danych, œrednie, mediany oraz odchylenia standardowe,
	które bêdzie nam mówiæ jak bardzo dane s¹ rozrzucone wokó³ œredniej.

	W tym pliku wystêpowa³ podobny problem z przecinkami co w pliku pierwszym, sposób postêpowania jest analogiczny. Tylko cudzys³owia pojawij¹ siê w dwóch pierwszych
	kolumnach, wiêc tutaj bêdziemy zaczynaæ od pêtli wczytuj¹cej kolumny z " " w razie ich wyst¹pienia. Dodatkowo wprowadzamy zmienn¹ licz¹c¹ wczytane kolumny,
	aby móc przerwaæ czytanie danych po zdobyciu wszystkich potrzebnych danych
	*/
	
	in.close();
	in.open("coffee_df.csv"); //otwieramy drugi plik


	unordered_map<string,Roast> roasts; // bêdziemy tu zawieraæ stopieN palenia kawy oraz obiekt typu Roast przechowuj¹cy dane danego stopnia palenia
	string roast_type; // zmienne pomocnicze do przechowywania danych
	int aroma;
	int acid;
	int flavor;
	int aftertaste;

	getline(in,s); //pierwszy wiersz jest nag³owkiem, wiêc go pomijamy

	// dane czytamy w identyczny sposób jak poprzednio
	while(getline(in,s)) // czytamy wiersz z pliku
	{
		line.clear(); // czyscimy wektor 
		stringstream str(s); //otwieramy strumieñ stringow
		
		while(str.get() == '"') //jeœli kolumny maj¹ " ", wczytujemy je
		{
			getline(str,word,'"');
			line.push_back(word);
			str.get();
		}
		str.unget();

		while(getline(str,word,','))
		{
			line.push_back(word);
			while(str.get() == '"') //jeœli kolumny maj¹ " ", wczytujemy je
			{
				getline(str,word,'"');
				line.push_back(word);
				str.get();
			}
			str.unget();
		}

		roast_type = line[2]; // wpisujemy stopieñ palenia kawy do zmiennej pomocniczej
		if(roasts.find(roast_type) == roasts.end()) //sprawdzamy, czy dany stopieñ palenia jest ju¿ w mapie
		{
			roasts[roast_type] = Roast(roast_type); //jeœli nie, dopisujemy go do naszej mapy i tworzymy dla niego obiekt Roast
		}

		try // funkcja stod musi byæ zawarta w try catch bloku, powniewa¿ inaczej generuje b³êdy...
		{
			aroma = stoi(line[6]); // przypisujemy wartoœci z wektora do zmiennych pomocniczych
			acid = stoi(line[7]);
			flavor = stoi(line[9]);
			aftertaste = stoi(line[10]);
			roasts[roast_type].Add_aroma(aroma); // wpisujemy wartoœci do wektorów metodami klasy
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
	for(auto pair : roasts) // dla ka¿dego stopnia palenia wypisujemy podsumowanie w formie ramki z danymi
	{
		cout << "--------------------------------------------------------------------------------\n";
		cout << "Roast type: " << setw(68) << pair.first << "|" <<endl; // typ palenia
		cout << setw(20) << "Aroma:" << setw(20) << "Acid:" << setw(20) << "Flavor:" << setw(20) << "Aftertaste" << "|" << endl; // nag³ówek
		cout << setw(10) << "Amount: " << setw(10) << pair.second.Size_of_vector(1); // liczba pomiarów 
		cout << setw(10) << "Amount: " << setw(10) << pair.second.Size_of_vector(2);
		cout << setw(10) << "Amount: " << setw(10) << pair.second.Size_of_vector(3);
		cout << setw(10) << "Amount: " << setw(10) << pair.second.Size_of_vector(4) << "|\n";
		cout << setw(10) << "Average: " << setw(10) << pair.second.Average(1); // œrednie 
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
	Dla lekkiego stopnia palenia charakterystyczna jest najwiêksza kwasowoœæ wynosz¹ca œrednio 8.57452. Aromat, smak i posmak takich ziaren jest œrednio nieco mniejszy, ni¿ dla ziaren Medium-Light. Dla tego typu najbardziej charakterystyczny jest smak kawy,
	wynosz¹cy œrednio 8.99856, odchylenie standardowe tej wartoœci wynosi zaldwie 0.294135, co oznacza, ¿e wszystkie wartoœci odbiegaj¹ od œredniej wartoœci tylko w niewielkim stopniu. Dla innych rodzajów ziaren mamy ju¿ du¿o mniej próbek, ale te¿
	mo¿emy z nich wyci¹gn¹æ pewne wnioski. Widzimy, ¿e od stopnia palenia Medium im bardziej s¹ pra¿one ziarna, tym bardziej malej¹ wszystkie z ich parametrów. Dla œredniego stopnia palenia najwiêkszy spadek nast¹pi³ dla kwasowoœci, wynosi ona zaledwie 8.15054.
	Dla Medium-Dark aromat, kwasowoœæ i posmak zmala³y o oko³o 0.5. Dla ziaren Dark kwasowoœæ i posmak spad³y poni¿ej 7, jedynym wzglêdnie wysokim parametrem pozostaje dla tych ziaren smak z œredni¹ 8.
	*/

	//------------------------------------------------------------------------------------------------------------------------------------------------------//

	/*
	WSTÊP
	Ostatnie zadanie tego programu, to znalezienie najbli¿szej kawiarni Starbuck do podanej przez u¿ytkowanika lokalizacji (d³ugoœci oraz szerokoœci geograficznej). Do tego celu potrzebujemy z pliku directory.csv nastêpuj¹cych kolumn: 12 - Longitude, 13 - Latitude oraz
	kolumny 3 - Store Name, 5 - Street Address oraz 6 - City do zwrócenia u¿ytkownikowi informacji o znalezionym przez program lokalu.
	*/

	in.close();
	in.open("directory.csv"); //otwieramy trzeci plik

	double longitude; // zmienne pomocnicze
	double latitude;
	double min_dist = 1000000; // poczatkowy dystans ma byæ teoretycznie nieskoñczonoœci¹, ale mo¿emy tu wstawiæ po prostu jakas du¿¹ liczbê
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

	getline(in,s); //pierwszy wiersz jest nag³owkiem, wiêc go pomijamy

	while(getline(in,s)) //czytamy po kolei linie
	{
		line.clear(); // czyœcimy wektor
		stringstream str(s); //otwieramy strumieñ stringów

		while(getline(str,word,',')) // dane rozdziela przecinek, wiêc czytamy po kolei pola
		{
			line.push_back(word); // dan¹ kolumne wrzucamy do wektora dla danej linii

			while(str.get() == '"') //rozwi¹zujemy problem z "" opisany we wstêpie
			{
				// jeœli tu weszliœmy, to oznacza ¿e trafiliœmy na kolumnê zawart¹ w " "
				getline(str,word,'"');
				line.push_back(word);
				str.get(); // zjadamy pozosta³y przecinek
			}
			str.unget(); // po wyjœciu z pêtli musimy zwróciæ znak który zjedliœmy
		}

		try // funkcja stod musi byæ zawarta w try catch bloku
		{
			if(line.size() == 13) // sprawdzamy, czy na pewno linia któr¹ wczytaliœmy jest kompletna
			{
				curr_dist = sqrt(pow(longitude-stod(line[11]),2) + pow(latitude-stod(line[12]),2)); // liczymy odleg³oœæ miêdzy dwoma punktami na mapie
				if(curr_dist < min_dist) // jeœli aktualna odleg³oœæ jest mniejsza ni¿ aktualnie zapisana odleg³oœæ minimalna to oznacza, ¿e znaleŸliœmy jeszcze bli¿szy sklep
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

