#include <iostream>
#include <time.h>

using namespace std;
/*
Создать абстрактный базовый класс Employer (служащий) с чисто виртуальной функцией Print(). 
Создайте три производных класса: President, Manager, Worker. Переопределите функцию Print()
для вывода информации, соответствующей каждому типу служащего. 
*/
//абстрактный базовый класс
class Employer
{
protected:
	int zp;
public:
	Employer(int z)	{	zp=z;	}
	//чисто виртуальна функция
	virtual void Print()=0;
};
class President: public Employer
{
public:
	President(int z): Employer(z) {}
	void Print()
	{
	cout << "\nI President zarpl="<<zp<<" $\n";
	}
};
class Manager: public Employer
{
public:
	Manager(int z): Employer(z){};
	void Print()
	{
	cout << "\nI Manager zarpl="<<zp<<" $\n";
	}
};
class Worker: public Employer
{
public:
	Worker(int z): Employer(z){};
	void Print()
	{
	cout << "\nI Worker zarpl="<<zp<<" $\n";
	}
};
/*
Создать базовый класс список. Реализовать на базе списка стек и очередь с виртуальными функциями вставки и вытаскивания. 
*/
//базовый класс список
class Spisok
{
protected:
	char *date;
	//количество елементов
	int Count;
	// Максимальный размер
	int MaxLength;
public:
	Spisok(int roz)
	{
		MaxLength=roz;
		Count=0;	
		try{
			date=new char[MaxLength]+1;
			if(*date==NULL)throw 1;
		}
		catch(int)
		{
			cout << "Error memoree\n";
			system("pause");
		}
	}	
	
	// Добавление элемента
	virtual void Adds(char c)=0;
	// Извлечение элемента
	virtual char Pop()=0;
	//показ
	virtual void Show()=0;
	// Количество элементов
	int GetCount(){	return Count;	};    
	// Проверка существования элементов
	bool IsEmpty(){	return Count==0;	};    
	// Проверка на переполнение
	bool IsFull(){	return Count>=MaxLength;	}; 
	//удаляум все , date=NULL для того что б не было ошыбки при повторном  Delall()
	void Delall(){	delete []date; 	MaxLength=Count=0;date=NULL;}
};
//стек
class Stek: public Spisok
{
public:
	Stek(int roz):Spisok(roz){};
	void Adds(char c)
	{
		// Если есть свободное место, то увеличиваем количество
		// значений и вставляем новый элемент

		if(!IsFull())
			date[Count++]=c;
	}
	char Pop()
	{
		// Если есть элементы, то возвращаем верхний и
		// уменьшаем указатель на вершину стека
		if(!IsEmpty())
			return date[--Count];
		else // Если в стеке элементов нет
			return 0;
	}
	void Show()
	{
		// пока не освободится
		char c;
	while(c=this->Pop())
	{
       		cout<<c<<" ";
	}
	cout<<"\n\n";
	}
};
//очередь
class Queue: public Spisok
{
public:
	Queue(int roz):Spisok(roz){};
	void Show()
	{
		cout<<"\n-------------------------------------\n";
		//демонстрация 
		for(int i=0;i<Count;i++)
		{
			cout << date[i]<<" ";
		}
		cout<<"\n-------------------------------------\n";

	}
	void Adds(char c)
	{
		// Если есть свободное место, то увеличиваем количество
		// значений и вставляем новый элемент
		if(!IsFull())
			date[Count++]=c;
	}
	char Pop()
	{
		// Если в очереди есть элементы, то возвращаем тот, 
		// который вошел первым и сдвигаем очередь	
	if(!IsEmpty())
	{
		//запомнить первый
		char temp=date[0];

		//сдвинуть все элементы
		for(int i=1;i < Count; i++)
			date[i-1]=date[i];

		//уменьшить количество
		Count--;

		//вернуть первый(нулевой)
		return temp;
	}

	else // Если в стеке элементов нет
		return -1;

	}
};
/*
Создать абстрактный базовый класс с виртуальной функцией - площадь. 
Создать производные классы: прямоугольник, круг, прямоугольный треугольник,
трапеция со своими функциями площади. Для проверки определить массив ссылок
на абстрактный класс, которым присваиваются адреса различных объектов.
*/
//абстрактный базовый класс с виртуальной функцией - площадь
class Areaq
{
protected:
	double S;
	double a,b,h,r;
	Areaq(){ S = a = b = h = r = 0; };
public:
	virtual double Area()=0;
};
//прямоугольник
class Rectangle : public Areaq
{public:
	double Area()
	{
		cout << "Rectangle\n";
		cout <<"Enter a double =";
		cin >> a;
		cout << "Enter b double =";
		cin >> b;
		S=a*b;
		return S;
	}
};
//круг
class Сircle : public Areaq
{public:
	double Area()
	{
		cout << "Circle\n";
		cout << "Enter radius double =";
		cin >> r;
		S=3.14*(r*r);
		return S;
	}
};
//прямоугольный треугольник
class Righttriangle : public Areaq
{public:
	double Area()
	{
		cout << "Righttriangle\n";
		cout << "Enter katet double (a)=";
		cin >> a;
		cout <<"Enter katet double (b)=";
		cin >> b;
		S=(a*b)/2;
		return S;
	}
};
//трапеция 
class Trapeze :public Areaq
{public:
	double Area()
	{
		cout << "Trapeze\n";
		cout << "Enter storona double (a)=";
		cin >> a;
		cout << "Enter storona double (b)=";
		cin >> b;
		cout << "Enter visota double (h)=";
		cin >> h;
		S=(a+b)*h/2;
		return S;
	}
};

void main()
{	
	srand(time(0));

	cout << "Areaq\n\n";
	Areaq *S[4] = {
		new Rectangle,
		new Сircle,
		new Righttriangle,
		new Trapeze,
	};
	
	double rectangle = S[0]->Area();
	cout << "Areaq : Rectangle = " << rectangle << endl;

	double circle =  S[1]->Area() ;
	cout << "Areaq : Circle = " << circle << endl;

	double righttriangle = S[2]->Area();
	cout << "Areaq : Righttriangle = " << righttriangle << endl;
	
	double trapeze = S[3]->Area();
	cout << "Areaq : Trapeze = " << trapeze << endl;

	system("pause");
	cout << "Queue\n\n";
	//создание очереди
	Queue QU(25);
	//заполнение части элементов
	for(int i=0;i<5;i++){
		QU.Adds(rand()%50);	}
	//показ очереди
	QU.Show();
	//извлечение элемента
	QU.Pop();
	//показ очереди
	QU.Show();
	
	system("pause");

	cout << "Employer\n\n";
	Employer *E[3]={	
		new President(100000),
		new Manager(50000),
		new Worker(15000)
	};
	 for(int i=0;i < 3;i++)
	E[i]->Print();
	 system("pause");
}	
