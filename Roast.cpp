#include "Roast.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <cmath>

using namespace std;

Roast::Roast() // konstruktor domyœlny
{

}
Roast::Roast(string n) // konstruktor jednoparametrowy
{
	roast = n;
}
void Roast::Add_aroma(int x) //funkcje dopisuj¹ce wartoœci na koniec 
{
	aroma.push_back(x);
}
void Roast::Add_acid(int x)
{
	acid.push_back(x);
}
void Roast::Add_flavor(int x)
{
	flavor.push_back(x);
}
void Roast::Add_aftertaste(int x)
{
	aftertaste.push_back(x);
}
void Roast::Print_vector()
{
	cout << left << setw(10) << "Aroma" << setw(10) << "Acid" << setw(10) << "Flavor" << setw(10) << "Aftertaste\n"; // nag³ówek
	for(int n=0; n < aroma.size(); n++)
	{
		cout << left << setw(10) << aroma[n] << setw(10) << acid[n] << setw(10) << flavor[n] << setw(10) << aftertaste[n] <<endl; //wypisujemy po kolei wartoœci z ka¿dego wektora
	}
}
double Roast::Average(int n) // argument decyduje o tym, dla jakiego wektora wykonujemy operacjê
{
	int size;
	// œrednie liczymy sumuj¹c wszystkie wartoœci wektora i dziel¹c t¹ sumê przez jego d³ugoœæ
	switch (n) {
	case 1:
		size = aroma.size();
		return accumulate(aroma.begin(),aroma.end(),0.0)/size;
	case 2:
		size = acid.size();
		return accumulate(acid.begin(),acid.end(),0.0)/size;
	case 3:
		size = flavor.size();
		return accumulate(flavor.begin(),flavor.end(),0.0)/size;
	case 4:
		size = aftertaste.size();
		return accumulate(aftertaste.begin(),aftertaste.end(),0.0)/size;
	}
	cout << "Wrong argument. Usage Average(n) where: 1 - average of aroma, 2 - average of acid, 3 - average of flavor, 4 - average of aftertaste\n";
}
int Roast::Median(int n)
{
	int size;
	// sortujemy wektor i zwracamy wartoœæ œrodkow¹
	switch(n) {
	case 1:
		size = aroma.size();
		sort(aroma.begin(),aroma.end());
		return aroma[size/2];
	case 2:
		size = acid.size();
		sort(acid.begin(),acid.end());
		return acid[size/2];
	case 3:
		size = flavor.size();
		sort(flavor.begin(),flavor.end());
		return flavor[size/2];
	case 4:
		size = aftertaste.size();
		sort(aftertaste.begin(),aftertaste.end());
		return aftertaste[size/2];
	}
	cout << "Wrong argument. Usage Median(n) where: 1 - median of aroma, 2 - median of acid, 3 - median of flavor, 4 - median of aftertaste\n";
}
double Roast::Standard_Deviation(int n)
{
	int size;
	double sum = 0;
	//liczymy odchylenie standardowe zgodnie ze wzorem - pierwiastek z sumy ró¿nic wszystkich wartoœci wektora i œredniej wartoœci do kwadratu 
	switch(n) {
	case 1:
		size = aroma.size();
		for(int x : aroma)
		{
			sum += pow(x - this->Average(1),2);
		}
		return sqrt(sum/size);
	case 2:
		size = acid.size();
		for(int x : acid)
		{
			sum += pow(x - this->Average(2),2);
		}
		return sqrt(sum/size);
	case 3:
		size = flavor.size();
		for(int x : flavor)
		{
			sum += pow(x - this->Average(3),2);
		}
		return sqrt(sum/size);
	case 4:
		size = aftertaste.size();
		for(int x : aftertaste)
		{
			sum += pow(x - this->Average(4),2);
		}
		return sqrt(sum/size);
	}
	cout << "Wrong argument. Usage Standard_Deviation(n) where: 1 - standard deviation of aroma, 2 - standard deviation of acid, 3 - standard deviation of flavor, 4 - standard deviation of aftertaste\n";
}

int Roast::Size_of_vector(int n)
{
	switch(n) {
	case 1:
		return aroma.size();
	case 2:
		return acid.size();
	case 3:
		return flavor.size();
	case 4:
		return aftertaste.size();
	}
	cout << "Wrong argument. Usage Size_of_vector(n) where: 1 - size of vector of aroma, 2 - size of vector of acid, 3 - size of vector of flavor, 4 - size of vector of aftertaste\n";
}