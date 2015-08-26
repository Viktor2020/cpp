#include<iostream>
using namespace std;
//Создайте класс Время, в котором реализованы операции сложения, вычитания, сравнения, ввода и вывод на экран. 
//Возможность конвертации времени из американского формата am (pm): 10:00 pm = 22:00, 12:00 pm =00:00 

//Создать класс для работы с матрицами. Предусмотреть, как минимум, функции для сложения матриц, умножения матриц, 
//транспонирования матриц, присваивания матриц друг другу, установка и получение произвольного элемента матрицы. 
//Необходимо перегрузить соответствующие операторы.

class Time
{
	
	int h,m;
	char *f;
public:
	Time(int hh=0,int mm=0,int am_pm=0)
	{
		h=hh%12;m=mm%60;
		if(am_pm)
			f="pm";
		else f="am";
	}
	void show()
	{
		cout << h << ":" << m << f << endl;
	}
	void input()
	{
		cout << "Enter the hours: ";
		cin >> this->h;this->h=this->h%12;
		cout << "Enter the minutes: ";
		cin >> this->m;this->m=this->m%60;
		cout << "Enter 1 = pm, or 2 = am: ";
		int f1;
		cin >> f1;
		if(f1==1)
			f="pm";
		else f="am";
	}
	Time conv()
	{
		if(this->f=="pm")
			this->h=this->h+12;
		this->f=" ";
		return *this;
	}
	Time operator ()(int hh=0,int mm=0,int am_pm=0)
	{
		h=hh%12;m=mm%60;
		if(am_pm)
			f="pm";
		else f="am";
		return *this;
	}
	Time operator=(Time a)
	{
		this->h=a.h;
		this->m=a.m;
		this->f=a.f;
		return *this;
	}
	Time operator+(Time a)
	{
		this->h+=a.h;
		if(this->h>12)
		{
			this->h=this->h%12;
		}
		this->m+=a.m;
		if(this->m>59)
		{
			this->m=this->m%60;
		}
		return *this;
	}
	Time operator-(Time a)
	{
		this->h-=a.h;
		if(this->h<0)
		{
			this->h=this->h%12;
			this->h=this->h*(-1);
		}
		this->m-=a.m;
		if(this->m<0)
		{
			this->m=this->m%60;
			this->m=this->m*(-1);		
		}
		return *this;
	}
	int operator==(Time a)
	{
		if(this->h==a.h && this->m==a.m )
		{cout << "Equal\n"; return 1;}
		else {cout << "Not equal\n";return 0;}
	}
};
class Matrix
{
	int **mas;
	int s,c;
public:
	Matrix(int st=1,int ct=1)		//конструктор
	{
		s=st;c=ct;
		mas = new int *[s];
		for (int i = 0; i < s; i++) 
		{
			mas[i] = new int [c];
		}
	}
	Matrix operator+(Matrix &ob)
	{
		if(c==ob.c && s==ob.s)
		{
		for(int i=0;i < s;i++)
			  for(int j=0;j < c;j++)
				  mas[i][j]=mas[i][j]+ob.mas[i][j];
		return *this;
		}
		else cout << "\n Matrix not indentifical[n][m]";
	}
	Matrix operator=(Matrix &ob)
	{
		if(c==ob.c && s==ob.s)
		{
		for(int i=0;i < s;i++)
			  for(int j=0;j < c;j++)
				  mas[i][j]=ob.mas[i][j];
		return *this;
		}
		else cout << "\nMatrix not indentifical[n][m]";
	}
	Matrix operator*(Matrix &ob)
	{
		if(c==ob.c && s==ob.s)
		{
		for(int i=0;i < s;i++)
			  for(int j=0;j < c;j++)
				  mas[i][j]=mas[i][j]*ob.mas[i][j];
		return *this;
		}
		else cout << "\nMatrix not indentifical[n][m]";
	}
	Matrix test(Matrix ob)
	{
		return ob;
	}
	Matrix transport()
	{
		Matrix temp;
		temp.s=this->s;
		temp.c=this->c;
		temp.mas = new int *[s];
		for (int i = 0; i < s; i++) 
		{
			temp.mas[i] = new int [c];
		}
		for(int i=0,t=1;i < s;i++)
			  for(int j=0;j < c;j++)
				temp.mas[i][j]=this->mas[i][j];
		free(mas);
		s=temp.c;c=temp.s;
		this->mas= new int *[s];
		for (int i = 0; i < s; i++) 
		{
			this->mas[i] = new int [c];
		}
		for(int i=0,b=0;i < s;i++,b++)
			for(int j=0,a=0;j < c;j++,a++)
				this->mas[i][j]=temp.mas[j][i];
		return *this;

	}
	int get(int st=0,int ct=0,int input_output_element=0)
	{
		if (input_output_element==1 && st <= s && ct <= c)	
		{
			 cout << mas[st][ct];
		}
		else if(input_output_element==0) cin >> mas[st][ct];
		else return mas[st][ct];
	}
	//показ матрицы
	void show()
	{
		for(int i=0;i < s;i++){
			cout << endl;
			  for(int j=0;j < c;j++)
				  cout << mas[i][j] << "\t";}cout << endl;
	}
	//заполнение матрицы
	void input(int avto=0,int st=1,int ct=1)
	{
		if(st > 1 && ct > 1)
			{s=st;c=ct;}
		else 
		{
			cout << "\nEnter Strok - ";
			cin >> s;
			cout << "\nEnter Stolb - ";
			cin >> c;
		}
		mas = new int *[s];
		for (int i = 0; i < s; i++) 
		{
			mas[i] = new int [c];
		}
		if(!avto)
		{
			for(int i=0,t=1;i < s;i++)
			  for(int j=0;j < c;j++)
				mas[i][j]=t++;
		}
		else for(int i=0;i < s;i++)
			for(int j=0;j < c;j++)
			{
				cout << "\nEnter element matrix ["<<i<<"]["<<j<<"] = ";
				cin >> mas[i][j];
			}
	}
	Matrix(Matrix & ob)		//конструктор копирования
	{
		this->c=ob.c;
		this->s=ob.s;
		this->mas = new int *[s];
		for (int i = 0; i < s; i++) 
		{
			this->mas[i] = new int [c];
		}
		for(int i=0;i < s;i++)
			for(int j=0;j < c;j++)
				this->mas[i][j]=ob.mas[i][j];
	}
	~Matrix()		//деструктор
	{
		delete [] mas;
		mas=NULL;//
	}

};

int main()
{
	setlocale( LC_ALL,"Russian" );
	enum ap{am,pm};
	enum mtr{input,output,element};
	Time t1,t2(1,00,pm);
	Matrix m1,m2;
	m1.test(m2);
	for(int x=1;x;)
	{
		cout << "\n1 - Создать матрицу1 розмерами N на M";
		cout << "\n2 - Получение произвольного элемента матрицы1";
		cout << "\n3 - Создать матрицу2 розмерами N на M";
		cout << "\n4 - Получение произвольного элемента матрицы2";
		cout << "\n5 - Матрицу1 + Матрицу2";
		cout << "\n6 - Матрицу1 * Матрицу2";
		cout << "\n7 - Матрицу1 = Матрицу2";
		cout << "\n8 - Транспонирования Матрицы1";
		cout << "\n9 - Транспонирования Матрицы2";
		cout << "\n10 - Очистить екран\n";
		cout << "\n0 - Выход\n";
	cin >> x;
	switch(x)
	{		
	case 1:
		  {				  
			  int a,b,c;
			  cout << "\nВедите N - "; cin >> a;
			  cout << "\nВедите M - "; cin >> b;
			  cout << "\nВедите 0 для авто, или 1 для ручного заполнения матрицы1 - "; cin >> c;
			  m1.input(c,a,b);m1.show();
		  break;}
	case 2:
		{	int a,b;
			cout << "\nВедитет елемент матрыцы1 [][]\n";cin >> a >> b;
			m1.get(a,b,output);
		break;}
	case 3:
		  {	int a,b,c;
			  cout << "\nВедите N - "; cin >> a;
			  cout << "\nВедите M - "; cin >> b;
			  cout << "\nВедите 0 для авто, или 1 для ручного заполнения матрицы2 - "; cin >> c;
			  m2.input(c,a,b);m2.show(); break;}
	case 4:
		  {	int a,b;
			cout << "\nВедитет елемент матрыцы2 [][]\n";cin >> a >> b;
			m1.get(a,b,output); break;}
	case 5:
		{	m1=m1+m2;m1.show();break;}
	case 6:
		  {	m1=m1*m2;m1.show();break;}
	case 7:
		  {	m1=m2;m1.show();	break;}
	case 8:
		{	m1.transport();m1.show();	break;}
	case 9:
		  {	m2.transport();m2.show();	break;}
	case 10:
		  {	system("cls");	break;}
	}
	}
	

	for(int x=1;x;)
	{
		cout << "\n1 - Введите time1 по умолчанию 00:00";
		cout << "\n2 - Введите time2 по умолчанию 00:00";
		cout << "\n3 - Показать time1";
		cout << "\n4 - Показать time2";
		cout << "\n5 - Конвектировать time1";
		cout << "\n6 - Конвектировать time2";
		cout << "\n7 - К первому времени  добавить (+) второе";
		cout << "\n8 - От первого времени отнять (-) второе";
		cout << "\n9 - Сравнить time1(==)time2 ";
		cout << "\n10 -Clear ";
		cout << "\n0 - Exit\n";
	cin >> x;
	switch(x)
	{		
	case 1:
		  {	t1.input();t1.show();break;}
	case 2:
		  {	t2.input();t2.show();break;}
	case 3:
		  {	t1.show(); break;}
	case 4:
		  {	t2.show(); break;}
	case 5:
		  {	t1.conv();t1.show();break;}
	case 6:
		  {	t2.conv();t2.show();break;}
	case 7:
		  {	t1=t1+t2;t1.show();	break;}
	case 8:
		  {	t1=t1-t2;t1.show();	break;}
	case 9:
		  {	t1==t2;	break;}
	case 10:
		  {	system("cls");	break;}
	}
	}
	system("pause");
	return 0;
}