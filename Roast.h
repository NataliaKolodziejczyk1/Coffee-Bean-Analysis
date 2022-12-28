#pragma once

#include <string>
#include <vector>
class Roast // klasa do analizy wp³ywu stopnia palenai na parametry kawy
{
private:
	std::string roast;
	std::vector<int> aroma;
	std::vector<int> acid;
	std::vector<int> flavor;
	std::vector<int> aftertaste;
public:
	Roast(); //konstruktor domyœlny
	Roast(std::string n); //konstruktor jednoparametrowy
	void Add_aroma(int x); // funkcje dodaj¹ce liczbê do wektorów
	void Add_acid(int x);
	void Add_flavor(int x);
	void Add_aftertaste(int x);
	void Print_vector(); // funkcja drukuj¹ca wektory 
	double Average(int n); //funkcja licz¹ca œredni¹ dla wektorów
	int Median(int n); // funkcja licz¹ca zwracaj¹ca mediane
	double Standard_Deviation(int n); //funkcja licz¹ca odchylenei standardowe
	int Size_of_vector(int n); // funkcja zwracaj¹ca d³ugoœæ wektora
};

