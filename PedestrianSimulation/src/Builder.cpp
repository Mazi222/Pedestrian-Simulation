#include "Builder.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>



Builder::Builder(const int & _i, const int & _j):row(_i+2),col(_j+2)
{
	tab = new char*[row];
	for(int p=0;p<row;++p)
		tab[p]=new char[col];
	for(int p=0;p<row;++p)
		for(int k=0;k<col;++k)
			tab[p][k]='w';
	name="out";
}

Builder::Builder()
{
	std::cout<< "Podaj wymiary planszy" << std::endl;
	int a,b;
	std::cin >> a;
	std::cin >> b;
	row=a+2;
	col=b+2;
	tab = new char*[row];
	for(int p=0;p<row;++p)
		tab[p]=new char[col];
	for(int p=0;p<row;++p)
		for(int k=0;k<col;++k)
			tab[p][k]='w';
	name="out";
}

Builder::~Builder()
{
	for(int p=0;p<row;++p)
		delete [] tab[p];
	delete [] tab;
}

std::pair<const std::string,const std::string> Builder::command_build()
{
	std::cout<<"\n Builder pliku glownego\n\n"<<std::endl;
	unsigned int h_count=0,p_count=0,a_count=0;
	int a,b;
	bool fl=true;
	std::string buf;
	std::stringstream tmp;
	_print_commands();
	std::string c_name;
	while(fl)
	{
		getline(std::cin,buf);
		tmp<<buf;
		tmp>>c_name;
		try{
			if(c_name=="help")
				_print_commands();
			else if(c_name=="q" || c_name=="quit")
				fl=false;
			else if(c_name=="show")
			{
				_show();
			}
			else if(c_name=="wall")
			{
				_check(tmp);
				tmp>>a;
				_check(tmp);
				tmp>>b;
				_add_wall(a+1,b+1);
			}
			else if(c_name=="plate")
			{
				_check(tmp);
				tmp>>a;
				_check(tmp);
				tmp>>b;
				_add_plate(a+1,b+1);
				++p_count;
			}
			else if(c_name=="splate")
			{
				_check(tmp);
				tmp>>a;
				_check(tmp);
				tmp>>b;
				_add_static_plate(a+1,b+1);
				++p_count;
			}
			else if(c_name=="human")
			{
				_check(tmp);
				tmp>>a;
				_check(tmp);
				tmp>>b;
				_add_human(a+1,b+1);
				++h_count;
			}
			else if(c_name=="atr")
			{
				_check(tmp);
				tmp>>a;
				_check(tmp);
				tmp>>b;
				_add_atractor(a+1,b+1);
				++a_count;
			}
			else if(c_name=="chname")
			{
				_check(tmp);
				tmp>>name;
			}
			else
				std::cout<<"Nieznana komenda"<<std::endl;
		}
		catch(outside_of_floor &ex)
		{
			std::cout<< "Podano wspolrzedne z poza zakresu, zakres to: " << row << " " << col
					<< " a podano: " << a << " " << b <<std::endl;
		}
		catch(not_enought_arguments &ex)
		{
			std::cout<< "Zbyt mala ilosc danych" <<std::endl;
		}
		catch(...)
		{
			std::cout<<"Nieznany blad "<<std::endl;
		}
		tmp.str("");
		tmp.clear();
	}

	std::ofstream plik(name);
	plik<< row << " " << col << std::endl;
	for(int p=0;p<row;++p)
	{
		for(int k=0;k<col;++k)
			plik<<tab[p][k];
		plik<<std::endl;
	}
	plik.close();

	command_build_ext(name,h_count,p_count,a_count);

	return std::pair<const std::string,const std::string>(name,name+"ext");

}

std::string Builder::command_build_ext(std::string name,const int &h,const int &p,const int &a)
{
	std::cout<<"\n\n\n Builder pliku dodatkowego\n\n"<<std::endl;
	int *hum=new int[h];
	int *plt=new int[p];
	int *atr=new int[a];

	std::fill_n(hum, h, 5);
	std::fill_n(plt, p, 5);
	std::fill_n(atr, a, 100);

	int b,c;
	bool fl=true;

	std::string buf;
	std::stringstream tmp;

	_print_commands_ext();
	std::string c_name;
	while(fl){
		buf.clear();
		tmp.clear();
		getline(std::cin,buf);
		tmp<<buf;
		tmp>>c_name;
		if(c_name=="help")
			_print_commands_ext();
		else if(c_name=="q" or c_name=="quit")
		{
			fl=false;
		}
		else if(c_name=="happines")
		{
			_check(tmp);
			tmp>>b;
			std::cout<< b <<std::endl;
			if(b<1 or b>=h+1)
			{
				std::cout<<"Poza tablica" <<std::endl;
			}
			else
			{
				_check(tmp);
				tmp>>c;
				hum[b-1]=c;
			}
			buf.clear();
			tmp.clear();
		}
		else if(c_name=="plate")
		{
			_check(tmp);
			tmp>>b;
			if(b<1 or b>=p+1)
			{
				std::cout<<"Poza tablica" <<std::endl;
			}
			else
			{
				_check(tmp);
				tmp>>c;
				plt[b-1]=c;
			}
			buf.clear();
			tmp.clear();
		}
		else if(c_name=="atr")
		{
			tmp>>b;
			if(b<0 or b>=a)
			{
				std::cout<<"Poza tablica" <<std::endl;
			}
			else
			{
				_check(tmp);
				tmp>>c;
				atr[b]=c;
			}
			buf.clear();
			tmp.clear();
		}
		else
		{
			std::cout<<"Nieznana komenda"<<std::endl;
		}
		std::cout<<"a"<<std::endl;
		buf.clear();
		tmp.clear();
	}
	name+="ext";
	std::ofstream plik(name);

	for(int i=0;i<h;++i)
		plik<<"h " << i << " " << hum[i] << std::endl;
	delete [] hum;

	for(int i=0;i<p;++i)
		plik<<"p " << i << " " << plt[i] << std::endl;
	delete [] plt;

	for(int i=0;i<a;++i)
		plik<<"a " << i << " " << atr[i] << std::endl;
	delete [] atr;

	plik.close();

	return name;
}

void Builder::_add_human(const int &a, const int &b)
{
	if(a-1>row || b-1>col)
		throw outside_of_floor(a,b);
	tab[a-1][b-1]='M';
}
void Builder::_add_wall(const int &a, const int &b)
{
	if(a-1>row || b-1>col)
		throw outside_of_floor(a,b);
	tab[a-1][b-1]='w';
}
void Builder::_add_plate(const int &a, const int &b)
{
	if(a-1>row || b-1>col)
		throw outside_of_floor(a,b);
	tab[a-1][b-1]='p';
}
void Builder::_add_static_plate(const int &a, const int &b)
{
	if(a-1>row || b-1>col)
		throw outside_of_floor(a,b);
	tab[a-1][b-1]='s';
}
void Builder::_add_atractor(const int &a, const int &b)
{
	if(a-1>row || b-1>col)
		throw outside_of_floor(a,b);
	tab[a-1][b-1]='a';
}


void Builder::_check(const std::stringstream &s)
{
	if(s.eof())
	{
		throw(not_enought_arguments());
	}
}

void Builder::_show(){
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			std::cout<<tab[i][j];
		}
		std::cout<<std::endl;
	}
}

void Builder::_print_commands()
{
	std::cout<<"help - pokazuje wszystkie komendy"<<std::endl;
	std::cout<<"show - pokazuje aktualna mape"<<std::endl;
	std::cout<<"wall x y - dodaje mur na (x,y)"<<std::endl;
	std::cout<<"plate x y - dodaje plytke na (x,y)"<<std::endl;
	std::cout<<"splate x y - dodaje plytke statyczna na (x,y)"<<std::endl;
	std::cout<<"human x y - dodaje czlowieka na (x,y)"<<std::endl;
	std::cout<<"atr x y - dodaje atraktor na (x,y)"<<std::endl;
	std::cout<<"chname name - zmienia nazwe pliku wyjsciowego"<<std::endl;
	std::cout<<"q or quit - koniec"<<std::endl;
}

void Builder::_print_commands_ext()
{
	std::cout<<"help - pokazuje wszystkie komendy"<<std::endl;
	std::cout<<"happines number_of_person value(0,-) - zmienia poczatkowa wartosc szczescia dla osoby, standardowe szczescie wynosi 5"<<std::endl;
	std::cout<<"plate number_of_plate value(0,-) - zmienia poczatkowa wartosc dla plytki dynamicznej"<<std::endl;
	std::cout<<"atr number_of_atractor value - zmienia wartosc przyciagania atraktora"<<std::endl;
	std::cout<<"q or quit - to leave"<<std::endl;
}
