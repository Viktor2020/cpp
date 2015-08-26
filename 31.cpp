// test.cpp: определ€ет точку входа дл€ консольного приложени€.
// 30.01.2014

#include <iostream>
#include <string>
using namespace std;
/*   
»спользу€ пон€тие множественного наследовани€, разработайте класс "ќкружность, вписанна€ в квадрат".
*/
class Okrusnost
{
protected:
	double radius;
	double dlina;
	double ploshyao;
	double diamtr;
	double pi;

public:
	// default constructor
	Okrusnost(){
		radius = dlina = ploshyao = diamtr = 0; 
		pi = 3.14; 
	}
	void setR(double r = 0)
	{
		if (!r)
		{
			cout << "Enter Radius okruznosti : ";
			cin >> radius;
		}
		else radius = r;
		diamtr = radius * 2;
		dlina = 2 * pi * radius;
		ploshyao = pi * (radius * radius);
	}
	void showO()
	{
		cout << "\nRadius : " << radius
			<< "\nDiamtr : " << diamtr
			<< "\nDlina : " << dlina
			<< "\nPloshay : " << ploshyao << "\n";
	}
};
class Kvadrat
{
protected:
	double storona;
	double ploshyak;
	double perimtr;
public:
	void setStorona(double s = 0)
	{
		if (!s)
		{
			cout << "Enter Storona kvadrata : ";
			cin >> storona;
		}
		else storona = s;
		perimtr = 4 * storona;
		ploshyak = storona * storona;
	}
	void showK()
	{
		cout << "\nStorona : " << storona
			<< "\nPerimtr : " << perimtr
			<< "\nPloshyak : " << ploshyak << "\n";
	}

};
class OvK : public Kvadrat, Okrusnost	//okruznostVkvadrate
{
public:
	void setOvK()
	{
		setStorona();
		setR(0.7 * storona);
	}
	void showOvK()
	{
		cout << "Okruznost v Kvadrate\n";
		showK();
		showO();
	}
}; 

int main()
{
	OvK OK;
	OK.setOvK();
	OK.showOvK();

	system("pause");
}
