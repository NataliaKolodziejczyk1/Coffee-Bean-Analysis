#pragma once
#include <string>
#include <vector>

class Country //klasa do analizy ocen kaw z poszczególnych krajów
{
private:
	std::string name; //nazwa kraju
	std::vector<double> cup_points; //wektor ocen
public:
	Country(); //konstrukt domyœlny
	Country(std::string n); //konstruktor jednoparametrowy
	void Add_cup_points(double x); //dopisanie oceny do wektora ocen
	void Print_vector(); //wypisanie wektora
	double Average_rating(); //liczenie œredniej oceny
	int Number_of_ratings(); //zwraca d³ugoœæ wektora ocen
};

