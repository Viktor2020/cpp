#include <iostream>
#include <time.h>

using namespace std;
/*
������� ����������� ������� ����� Employer (��������) � ����� ����������� �������� Print(). 
�������� ��� ����������� ������: President, Manager, Worker. �������������� ������� Print()
��� ������ ����������, ��������������� ������� ���� ���������. 
*/
//����������� ������� �����
class Employer
{
protected:
	int zp;
public:
	Employer(int z)	{	zp=z;	}
	//����� ���������� �������
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
������� ������� ����� ������. ����������� �� ���� ������ ���� � ������� � ������������ ��������� ������� � ������������. 
*/
//������� ����� ������
class Spisok
{
protected:
	char *date;
	//���������� ���������
	int Count;
	// ������������ ������
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
	
	// ���������� ��������
	virtual void Adds(char c)=0;
	// ���������� ��������
	virtual char Pop()=0;
	//�����
	virtual void Show()=0;
	// ���������� ���������
	int GetCount(){	return Count;	};    
	// �������� ������������� ���������
	bool IsEmpty(){	return Count==0;	};    
	// �������� �� ������������
	bool IsFull(){	return Count>=MaxLength;	}; 
	//������� ��� , date=NULL ��� ���� ��� � �� ���� ������ ��� ���������  Delall()
	void Delall(){	delete []date; 	MaxLength=Count=0;date=NULL;}
};
//����
class Stek: public Spisok
{
public:
	Stek(int roz):Spisok(roz){};
	void Adds(char c)
	{
		// ���� ���� ��������� �����, �� ����������� ����������
		// �������� � ��������� ����� �������

		if(!IsFull())
			date[Count++]=c;
	}
	char Pop()
	{
		// ���� ���� ��������, �� ���������� ������� �
		// ��������� ��������� �� ������� �����
		if(!IsEmpty())
			return date[--Count];
		else // ���� � ����� ��������� ���
			return 0;
	}
	void Show()
	{
		// ���� �� �����������
		char c;
	while(c=this->Pop())
	{
       		cout<<c<<" ";
	}
	cout<<"\n\n";
	}
};
//�������
class Queue: public Spisok
{
public:
	Queue(int roz):Spisok(roz){};
	void Show()
	{
		cout<<"\n-------------------------------------\n";
		//������������ 
		for(int i=0;i<Count;i++)
		{
			cout << date[i]<<" ";
		}
		cout<<"\n-------------------------------------\n";

	}
	void Adds(char c)
	{
		// ���� ���� ��������� �����, �� ����������� ����������
		// �������� � ��������� ����� �������
		if(!IsFull())
			date[Count++]=c;
	}
	char Pop()
	{
		// ���� � ������� ���� ��������, �� ���������� ���, 
		// ������� ����� ������ � �������� �������	
	if(!IsEmpty())
	{
		//��������� ������
		char temp=date[0];

		//�������� ��� ��������
		for(int i=1;i < Count; i++)
			date[i-1]=date[i];

		//��������� ����������
		Count--;

		//������� ������(�������)
		return temp;
	}

	else // ���� � ����� ��������� ���
		return -1;

	}
};
/*
������� ����������� ������� ����� � ����������� �������� - �������. 
������� ����������� ������: �������������, ����, ������������� �����������,
�������� �� ������ ��������� �������. ��� �������� ���������� ������ ������
�� ����������� �����, ������� ������������� ������ ��������� ��������.
*/
//����������� ������� ����� � ����������� �������� - �������
class Areaq
{
protected:
	double S;
	double a,b,h,r;
	Areaq(){ S = a = b = h = r = 0; };
public:
	virtual double Area()=0;
};
//�������������
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
//����
class �ircle : public Areaq
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
//������������� �����������
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
//�������� 
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
		new �ircle,
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
	//�������� �������
	Queue QU(25);
	//���������� ����� ���������
	for(int i=0;i<5;i++){
		QU.Adds(rand()%50);	}
	//����� �������
	QU.Show();
	//���������� ��������
	QU.Pop();
	//����� �������
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
