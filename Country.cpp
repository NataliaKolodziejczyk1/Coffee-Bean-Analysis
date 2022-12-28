#include "Country.h"
#include "iostream"
#include <numeric>

using namespace std;

Country::Country() { } // konstruktor domyœlny
Country::Country(string n) // konstruktor jednoparametrowy
{
	name = n;
}
void Country::Add_cup_points(double x)
{
	cup_points.push_back(x); // na koniec wektora dopisujemy podan¹ jako argument wartoœæ
}
void Country::Print_vector()
{
	for(double x : cup_points) 
	{
		cout << x << endl;
	}
}
double Country::Average_rating()
{
	int size = cup_points.size();
	return accumulate(cup_points.begin(),cup_points.end(),0.0)/size; // sumujemy wszystkie wartoœci wektora i dzielimy przez jego rozmiar
}
int Country::Number_of_ratings()
{
	return cup_points.size(); 
}
