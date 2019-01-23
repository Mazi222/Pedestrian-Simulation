#include "Floor.h"

#include <vector>
#include <utility>
#include <fstream>

Floor::Floor()
{
	const std::pair<const std::string,const std::string> name=_build_floor();
	_load(name);
}

Floor::Floor(const int &a, const int &b)
{
	const std::pair<const std::string,const std::string> name=_build_floor(a,b);
	_load(name);
}

Floor::Floor(const std::pair<const std::string,const std::string> &name)
{
	_load(name);
}

void Floor::_build_map(const int &a, const int &b)
{
	si.first=a;
	si.second=b;
	mapa=new std::pair<char,int>*[a];
	for(int i=0;i<a;++i)
		mapa[i]=new std::pair<char,int>[b];
}

void Floor::_build_human_map(const int &a, const int &b)
{
	map_p=new int *[a];
	for(int i=0;i<a;++i)
		map_p[i]=new int [b];
	for(int i=0;i<a;++i)
		for(int j=0;j<b;++j)
			map_p[i][j]=-1;
}

void Floor::_load(const std::pair<const std::string,const std::string> &name)
{
	Interpreter inter(this);
	inter.read(name.first);
	for(unsigned int i=0;i<plytki.size();++i)
	{
		plytki[i].calculate_plate_value(atraktory);
	}
	try{
		inter.read_additional(name.second);
	}
	catch(not_open &p)
	{
		//std::cerr<<"Nie udalo sie odczytac dodatkowych danych"<<std::endl;
	}
	for(int i=0;i<si.first;++i)
	{
		for(int j=0;j<si.second;++j)
		{
			if(map_p[i][j]!=-1)
				plytki[mapa[i][j].second].is_free=0;
		}
	}
}

Floor::~Floor()
{
	for(int i;i<si.first;++i)
		delete [] mapa[i];
	delete [] mapa;
}



std::pair<const std::string,const std::string> Floor::_build_floor(const int &row, const int &col)
{
	if(row != 0 && col !=0)
	{
		Builder build(row,col);
		return build.command_build();
	}
	else
	{
		Builder build;
		return build.command_build();
	}
}

void Floor::move_x_step(const unsigned int & st_numb)
{
	Observer ob(*this);
	char change=0;
	for(unsigned int i=0;i<st_numb;++i)
	{
		_move(change);
		if(change==1)
			ob.write();
		change=0;
	}
	ob.final();
	_save();
}

void Floor::move_untill_end()
{
	Observer ob(*this);
	char change=0;
	while(ludzie.size())
	{
		_move(change);
		if(change==1)
			ob.write();
		change=0;
	}
	ob.final();
	_save();
}

				/* FLOOR PRIVATE SECTION */

void Floor::_move(char &change)
{
	std::pair<int,int> tmp;
	std::pair<int,int> now;

	_calculate();

	for(int i=0;i<ludzie.size();++i)
	{
		tmp=ludzie[i].wsp;
		now=ludzie[i].move(plytki,mapa);
		if(tmp!=now)
		{
			change=1;
			if(plytki[mapa[tmp.first][tmp.second].second].is_static == true)
				mapa[tmp.first][tmp.second].first='s';
			else
				mapa[tmp.first][tmp.second].first='p';
			plytki[mapa[tmp.first][tmp.second].second].is_free=1;
			plytki[mapa[tmp.first][tmp.second].second].val+=-3;
			map_p[now.first][now.second]=map_p[tmp.first][tmp.second];
			map_p[tmp.first][tmp.second]=-1;
			plytki[mapa[now.first][now.second].second].is_free=0;
			map_p[tmp.first][tmp.second]=0;
			mapa[now.first][now.second].first='M';
			//std::cout<<  now.first << " " << now.second << std::endl;
			ludzie[i].wsp.first=now.first;
			ludzie[i].wsp.second=now.second;
			ludzie[i].end(atraktory);
		}
	}
	_kill();
}

void Floor::_calculate()
{
	for(int i=0;i<ludzie.size();++i)
	{
		ludzie[i].set_pref(plytki,mapa);
	}
}


void Floor::_move_person(const std::pair<int,int> &p, const std::pair<int,int> &k,std::vector<cnt::Person>::iterator &it)
{
	mapa[p.first][p.second].first='p';
	if(mapa[k.first][k.second].first=='s')
		(*it).alive=false;
	else
		mapa[k.first][k.second].first='M';
}


void Floor::_save(const std::string &name_out)const          // "Result"
{
	std::ofstream plik(name_out);
	for(int i=0;i<si.first;++i)
	{
		for(int j=0;j<si.second;++j)
		{
			plik<<mapa[i][j].first;
		}
		plik<<std::endl;
	}
	std::ofstream plik2(name_out+"ext");
	for(int i=0;i<plytki.size();++i)
	{
		plik2 << 'p' << ' ' << i << ' ' << plytki[i].val << std::endl;
	}
	for(int i=0;i<ludzie.size();++i)
	{
		plik2 << 'h' << ' ' << i << ' ' << ludzie[i].happines << std::endl;
	}
	for(int i=0;i<ludzie.size();++i)
	{
		plik2 << 'a' << ' ' << i << ' ' << atraktory[i].power << std::endl;
	}
}
void Floor::_kill()
{
	for(unsigned int i=0;i<ludzie.size();++i)
	{
		if(!(ludzie[i].alive))
		{
			plytki[mapa[ludzie[i].wsp.first][ludzie[i].wsp.second].second].is_free=1;
			if(plytki[mapa[ludzie[i].wsp.first][ludzie[i].wsp.second].second].is_static==true)
				mapa[ludzie[i].wsp.first][ludzie[i].wsp.second].first='s';
			else
				mapa[ludzie[i].wsp.first][ludzie[i].wsp.second].first='p';
			ludzie.erase(ludzie.begin()+i);
			--i;
		}
	}
}

				/* INTERPRETER */

void Interpreter::read(const std::string &name)
{
	std::string buf;
	unsigned int i=0,j=0;
	std::ifstream plik(name);
	if(!plik)
		throw not_open(name);
	int a,b;
	getline(plik,buf);
	std::stringstream ss;
	ss<<buf;
	ss>>a;
	ss>>b;
	fp->_build_map(a,b);
	fp->_build_human_map(a,b);
	while(plik)
	{
		getline(plik,buf);
		for(int t=0;t<buf.size();++t)
		{
			switch(buf[t])
			{
			case 'p': _add_plate(i,j);
				break;// plytka
			case 'w': _add_wall(i,j);
				break;//sciana
			case 'M': _add_human(i,j);
				break;//czlowiek
			case 's': _add_plate(i,j,true);
				break;// plytka statyczna
			case 'a': _add_attractor(i,j);
				break; //atraktor
			default:
				throw(symbol_is_not_in_base(buf[t]));
				break;
			}
			++j;
		}
		++i;
		j=0;
		//buf.clear();
	}
	plik.close();
}

void Interpreter::read_additional(const std::string &name)
{
	std::string buf;
	std::stringstream ss;
	int a,b;
	char tmp;
	std::ifstream plik(name);
	if(!plik)
		throw not_open(name);
	while(plik)
	{
		getline(plik,buf);
		ss<<buf;
		ss>>tmp;
		try{
		_check(ss);
		}
		catch(not_enought_arguments &p)
		{
			std::cerr<<"Nie wystarczajaca ilosc argumentow"<<std::endl;
		}
		ss>>a;
		ss>>b;
		switch(tmp)
		{
		case 'p': _set_plate_value(a,b);
			break;
		case 'h': _set_human_happines(a,b);
			break;
		case 'a': _set_attractor_power(a,b);
			break;
		default:
			throw(symbol_is_not_in_base(tmp));
			break;
		}
		ss.str("");
		ss.clear();
	}

}

void Interpreter::_add_plate(const unsigned int &i, const unsigned int &j,const bool is_static)
{
	fp->plytki.push_back(cnt::Plate(std::pair<int,int>(i,j),is_static));
	if(is_static)
		fp->mapa[i][j].first='s';
	else
		fp->mapa[i][j].first='p';
	fp->mapa[i][j].second=fp->plytki.size();
}

void Interpreter::_add_wall(const unsigned int &i, const unsigned int &j)
{
	fp->sciany.push_back(cnt::Wall(std::pair<int,int>(i,j)));
	fp->mapa[i][j].first='w';
	fp->mapa[i][j].second=fp->sciany.size();

}

void Interpreter::_add_human(const unsigned int &i, const unsigned int &j)
{
	fp->ludzie.push_back(cnt::Person(std::pair<int,int>(i,j)));
	_add_plate(i,j);
	fp->mapa[i][j].first='M';
	fp->map_p[i][j]=fp->ludzie.size();

}

void Interpreter::_add_attractor(const unsigned int &i, const unsigned int &j)
{
	fp->atraktory.push_back(cnt::Attractor(std::pair<int,int>(i,j)));
	fp->mapa[i][j].first='a';
	fp->mapa[i][j].second=fp->atraktory.size();
}

void Interpreter::_set_plate_value(const unsigned int &i, const unsigned int &j)
{
	fp->plytki[i].set_value(j);
}
void Interpreter::_set_human_happines(const unsigned int &i, const unsigned int &j)
{
	fp->ludzie[i].set_happines(j);
}
void Interpreter::_set_attractor_power(const unsigned int &i, const unsigned int &j)
{
	fp->atraktory[i].set_power(j);
}

void Interpreter::_check(const std::stringstream &s)const
{
	if(s.eof())
		throw(not_enought_arguments());
}

Observer::Observer(const Floor &p):fr(p),plik("allrecords"){}

void Observer::write(){
	plik<<std::endl;
	for(int i=0;i<fr.si.first;++i)
	{
		for(int j=0;j<fr.si.second;++j)
			plik<<fr.mapa[i][j].first;
		plik<<std::endl;
	}
}

void Observer::final()
{
	int height=fr.si.first*20;
	int width=fr.si.second*20;
	std::ofstream intbmp("intbmp");
	for(int i=1;i<fr.si.first;++i)
	{
		intbmp <<'L' << ' ' << i*20 << ' ' << 0 << ' ' << i*20<< ' ' << width << ' ' << 255 << ' ' << 255 << ' ' << 0 <<std::endl;
	}
	for(int i=1;i<fr.si.second;++i)
	{
		intbmp <<'L' << ' ' << 0 << ' ' << i*20 << ' ' << height<< ' ' << i*20 << ' ' << 255 << ' ' << 255 << ' ' << 0 <<std::endl;
	}
	for(int i=0;i<fr.si.first;++i)
	{
		for(int j=0;j<fr.si.second;++j)
		{
			if(fr.mapa[i][j].first=='M')
			{
				intbmp << 'C' << ' ' << j*20 + 10  << ' ' << i*20 + 10<< ' ' << 10 << ' ' << 255 << ' ' << 255 << ' ' << 255 <<std::endl;
			}
			else if(fr.mapa[i][j].first=='a')
			{
				intbmp << 'D' << ' ' << i*20 + 10 << ' ' << j*20 + 10 << ' ' << 10 << ' ' << 255 << ' ' << 0 << ' ' << 255 <<std::endl;
			}
		}
	}
}




