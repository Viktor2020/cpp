#include <iostream>
#include <map>
#include <vector>
#include <algorithm>	//max_element
//#include <iterator>	
#include <time.h>	//rand
#include <Windows.h>	//sleep
using namespace std;

enum Suit{HEARTS=3, DIAMONDS, CLUBS, SPADES};

class Deck {
	pair<int,Suit> card[52];	//������ ���� �� 52 ��������
	pair<int,Suit> _card[52];	//�����-������������� �����		
	int size_d,size_g;		//������ ������, ���-�� ������
	//--------------------------------------
	//������ ����� � �����
	void Throw (int t) 
	{
		_card[size_g++]=card[t];
	}
	//--------------------------------------
	//��� �������� ����� �����?
	bool isAllow(pair<int,Suit> temp) {			
		for (int i=0;i<size_g;i++)
			if (temp.first == _card[i].first && temp.second == _card[i].second)
				return false;
		return true;
	}
	//--------------------------------------
	//����������� ������
	void Shuffle() {
		cout << "\n����������� ����...\n";
		size_g=0;
	}
	//--------------------------------------
public:
	Deck(){				
		size_d=52;
		size_g=0;
		int i=0;						//������������� ������
		for (int j=0;j<13;j++) {
			card[i*13+j].first=j;
			card[i*13+j].second=HEARTS;
		} i++;
		for (int j=0;j<13;j++) {
			card[i*13+j].first=j;
			card[i*13+j].second=DIAMONDS;
		} i++;
		for (int j=0;j<13;j++) {
			card[i*13+j].first=j;
			card[i*13+j].second=CLUBS;
		} i++;
		for (int j=0;j<13;j++) {
			card[i*13+j].first=j;
			card[i*13+j].second=SPADES;
		}
	}
	~Deck(){}
	//�������� ��������� ����� �� ������
	const pair<int,Suit> getCard() 
	{
//		cout << size_g << endl;	//���������� ���� � ������
		if(size_g>40)
			Shuffle();		//�����������
		int t;
		while (!isAllow(card[t=rand()%52])) {}
		Throw(t);	//������ ����� � �����
		return card[t];
	}
	//--------------------------------------
	//�������� ������
	void print()
	{
		for(int i=0;i < 52;i++)
		{
			if(card[i].first>8)
			switch (card[i].first) 
			{
				case 9: cout<<"J"<< (char)card[i].second << endl; break;
				case 10:cout<<"Q"<< (char)card[i].second << endl; break;
				case 11:cout<<"K"<< (char)card[i].second << endl; break;
				case 12:cout<<"A"<< (char)card[i].second << endl; break;
			}
			else
				cout << card[i].first+2 << ' ' << (char)card[i].second <<"\n";
		}	
	}
};

class Hand
{
	multimap<int,Suit>hands;	//����� �� �����
	multimap<int,Suit>::const_iterator iter;	//��� ���������
	int power;	//���� ����� 
	int kiker;	//���� ������
	//--------------------------------------
	//����?
	bool isKare() 
	{
		iter=hands.begin();
		int flag=0;//����� ���������
		for(;iter != hands.end();iter++)
		{
			flag = hands.count(iter->first);
			if(flag == 4)
			{
				setPower();
				setKiker();
				return true;
			}
		}
		return false;
	}
	//--------------------------------------
	//����?
	bool isFlush()
	{
		iter=hands.begin();
		multimap<Suit,int> temp;	//����� �������� (����� ����� ��������)
		while(iter != hands.end())
		{
			temp.insert(pair<Suit,int>(iter->second,iter->first));
			iter++;
		}
		multimap<Suit,int>::iterator s = temp.begin();
		int flag=0;	//����� ��������� �����
		flag = temp.count(s->first);
		if(flag==temp.size())	 
		{
			setPower();
			return true;
		}			
		return false;
	}
	//--------------------------------------
	//�����?
	bool isStraight()
	{
		iter=hands.begin();
		int flag=0;
		multimap<int,Suit>::const_iterator itemp=hands.begin();
		itemp++;
		for(;itemp != hands.end();iter++,itemp++)
			if((iter->first+1)==(itemp->first))
				flag++;	
		if(flag==4)
		{
			setPower();
			return true;
		}			
		return false;
	}
	//--------------------------------------
	//������?
	bool isSet()
	{
		iter=hands.begin();
		int flag=0;//����� ���������
		for(;iter != hands.end();iter++)
		{
			flag = hands.count(iter->first);
			if(flag == 3)
			{
				setPower();
				setKiker();
				return true;
			}
		}
		return false;
	}
	//--------------------------------------
	//��� ����?
	bool isTwoPair()
	{
		iter=hands.begin();
		int flag=0;//����� ���������
		int par=0;//����� ���
		for(;iter != hands.end();iter++)
		{
			flag = hands.count(iter->first);
			if(flag == 2)
				par++;
		}
		if(par == 4)
		{
			setPower();
			setKiker();
			return true;
		}
		return false;
	}
	//--------------------------------------
	//����?
	bool isPair()
	{
		iter=hands.begin();
		int flag=0;//����� ���������
		for(;iter != hands.end();iter++)
		{
			flag = hands.count(iter->first);
			if(flag == 2)
			{
				setPower();
				setKiker();
				return true;
			}				
		}
		return false;
	}
	//--------------------------------------
	//����� ����?
	bool isStraightFlush()
	{
		if(isStraight() && isFlush())
			return true;
		return false;
	}
	//--------------------------------------
	//���-����?
	bool isFullHouse()
	{
		if(isPair() && isSet())
			return true;
		return false;
	}
	//--------------------------------------
	//����-����?
	bool isRoyalFlush()
	{
		if(isAce() && isFlush() && isStraight())
			return true;
		return false;
	}
	//--------------------------------------
	//���� ���?
	bool isAce()
	{
		return hands.count(12) ? true : false;
	}
	//--------------------------------------
	//����� � ��������� ������
	void setKiker()
	{
		iter=hands.begin();
		int flag=0;//����� ���������
		vector<int> V;
		V.push_back(0);
		vector<int>::iterator iV = V.begin();
		for(;iter != hands.end();iter++)
		{
			flag = hands.count(iter->first);
			if(flag == 1)		//���� ����� ����������� ���� ���
				V.push_back(iter->first);
		}
		kiker = (*max_element( V.begin(), V.end() ));	//
	}
	//--------------------------------------
	//���������� ���� �����
	void setPower()
	{
		power = 0;
		iter=hands.begin();
		for(;iter != hands.end();iter++)
			power+=iter->first;			
	}
	//--------------------------------------
	//��������� ���� ���� �� �����
	void Count() 
	{
		if		(isRoyalFlush())	{power+=200;cout << "\nYou have RoyalFlush \n";}
		else if (isStraightFlush())	{power+=180;cout << "\nYou have StraightFlush \n";}
		else if (isKare())			{power+=160;cout << "\nYou have Kare \n";}
		else if (isFullHouse())		{power+=140;cout << "\nYou have FullHouse \n";}
		else if (isFlush())			{power+=120;cout << "\nYou have Flush \n";}
		else if (isStraight() )		{power+=100;cout << "\nYou have Straight \n";}
		else if (isSet())			{power+=60; cout << "\nYou have Set \n";}
		else if (isTwoPair())		{power+=40; cout << "\nYou have TwoPair\n";}
		else if (isPair())			{power+=20; cout << "\nYou have Pair \n";}
		else 
		{
			setKiker();
			cout << "\nYou have Card\n";
		}
	}
	//--------------------------------------
public:
	//
	Hand():power(0),kiker(0){}
	//--------------------------------------
	bool operator==(Hand temp) 
	{
		if (power==temp.power && kiker==temp.kiker)
			return true;
		return false;
	}
	//--------------------------------------
	bool operator>(Hand temp) 
	{
		if (power>temp.power)
			return true;
		else if (power==temp.power && kiker>temp.kiker)
			return true;
		return false;
	}
	//--------------------------------------
	//����� ����������� �� �����
	void show()
	{
		int num=1;
		iter=hands.begin();
		for(; iter != hands.end();iter++)
		{
			if(iter->first>8)
			switch (iter->first) 
			{
				case 9: cout<<num++<<"-\t"<<"J"<< (char)iter->second << endl; break;
				case 10:cout<<num++<<"-\t"<<"Q"<< (char)iter->second << endl; break;
				case 11:cout<<num++<<"-\t"<<"K"<< (char)iter->second << endl; break;
				case 12:cout<<num++<<"-\t"<<"A"<< (char)iter->second << endl; break;
			}
			else
				cout << num++ <<"-\t"<< iter->first+2 << "" << (char)iter->second << endl;

		}
		cout<<"\nPower= "<<power<<endl;
		cout<<"Kiker= "<<kiker<<endl;
		cout << endl << endl;
	}	
	//--------------------------------------
	//������������� ����
	void init(Deck &k)
	{
		//-------------test_kod
		/*hands.insert(pair<int, Suit>(2,CLUBS));
		hands.insert(pair<int, Suit>(2,CLUBS));
		hands.insert(pair<int, Suit>(3,SPADES));
		hands.insert(pair<int, Suit>(3,CLUBS));
		hands.insert(pair<int, Suit>(3,CLUBS));
		hands.insert(pair<int, Suit>(6,CLUBS));
		hands.insert(pair<int, Suit>(7,SPADES));
		hands.insert(pair<int, Suit>(8,HEARTS));
		hands.insert(pair<int, Suit>(9,CLUBS));
		hands.insert(pair<int, Suit>(2,SPADES));
		hands.insert(pair<int, Suit>(11,HEARTS));
		hands.insert(pair<int, Suit>(2,HEARTS));*/
		//--------------
		while(hands.size()<5)
		{
			hands.insert(k.getCard());	//�������� ��������� ����� �� ������
			Sleep(100);
		}
		Count();	//��������� ���� ���� �� �����
		show();		//����� ����������� �� �����
	}
	//--------------------------------------
	//�������� �����
	void reCard(Deck &kol)
	{
		cout << "\n����� ����� ������? ";
		char ans;
		cin >> ans;
		while((ans<'0' || ans>'5'))
		{
			cout << "\n����� ����� �� 1 �� 5! ";
			cin >> ans;
		}
		multimap<int,Suit>::const_iterator it = hands.begin();
		for(char flag='1'; it != hands.end();it++,flag++)
		{
			if(flag==ans)
			{
				hands.erase(it);
				init(kol);
				break;
			}
		}
	}
	//--------------------------------------
	//������� ��� �����
	void pick_up()
	{
		hands.clear();
	}
};
	//����
	void theGame(Hand &play, Hand &comp, Deck &kol)
	{
		play.init(kol);		//������������� ����
		cout << "������ �����? (y/n) ";
		char c;
		cin >> c;
		if(c=='y')
			play.reCard(kol);	//�������� �����
		comp.init(kol);
		//system("cls");
		if(play==comp)
		{
			cout << "����� ���������� �������� �������\n ";
			return;
		}
		
		cout << "play cards = \n";
		play.show();
		cout << "comp cards = \n";
		comp.show();
		if (play > comp){
			cout << "� ������ ����� �������\n";
		}
		else {
			cout << "� ��������� ����� �������\n";
		}
		cout << "\n\n��� ������? (y/n)";
		cin >> c;
		if(c=='y')
		{
			play.pick_up();	//������� �����
			comp.pick_up();	//������� �����
			theGame(play,comp,kol);
		}
	}
	//--------------------------------------

int main() {
	setlocale(0,"RUS");
	srand((unsigned)time(0));
	//--------------------------------------
	Deck kol;	//������
//	kol.print();
	Hand play , comp;	
	theGame(play,comp,kol);
	system("pause");

	//system("pause");
	return 0;
}