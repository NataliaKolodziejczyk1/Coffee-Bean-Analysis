#pragma once

#include <string>
#include <vector>
class Roast // klasa do analizy wp�ywu stopnia palenai na parametry kawy
{
private:
	std::string roast;
	std::vector<int> aroma;
	std::vector<int> acid;
	std::vector<int> flavor;
	std::vector<int> aftertaste;
public:
	Roast(); //konstruktor domy�lny
	Roast(std::string n); //konstruktor jednoparametrowy
	void Add_aroma(int x); // funkcje dodaj�ce liczb� do wektor�w
	void Add_acid(int x);
	void Add_flavor(int x);
	void Add_aftertaste(int x);
	void Print_vector(); // funkcja drukuj�ca wektory 
	double Average(int n); //funkcja licz�ca �redni� dla wektor�w
	int Median(int n); // funkcja licz�ca zwracaj�ca mediane
	double Standard_Deviation(int n); //funkcja licz�ca odchylenei standardowe
	int Size_of_vector(int n); // funkcja zwracaj�ca d�ugo�� wektora
};

