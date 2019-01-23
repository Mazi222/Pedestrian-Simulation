#include "Cotainers.h"

namespace cnt {


					/* PERSON */


Person::Person(const std::pair<int,int> &pai,const double &happy):wsp(pai),happines(happy),alive(true),moved(false),
		best(0),best2(0),best3(0){}

void Person::set_pref(std::vector<Plate> &pl,std::pair<char,int> **map)
{
	best=0;
	best2=0;
	best3=0;
	if(map[wsp.first+1][wsp.second].first=='p' || map[wsp.first+1][wsp.second].first=='s')
	{
		pl[map[wsp.first+1][wsp.second].second].set_or_check_max(happines);
		if(pl[map[wsp.first+1][wsp.second].second].max>best)
		{
			best3=best2;
			best2=best;
			best=pl[map[wsp.first+1][wsp.second].second].max;
		}
	}
	if(map[wsp.first][wsp.second+1].first=='p' || map[wsp.first][wsp.second+1].first=='s')
	{
		pl[map[wsp.first][wsp.second+1].second].set_or_check_max(happines);
		if(pl[map[wsp.first][wsp.second+1].second].max>best)
		{
			best3=best2;
			best2=best;
			best=pl[map[wsp.first][wsp.second+1].second].max;
		}
	}
	if(map[wsp.first-1][wsp.second].first=='p' || map[wsp.first-1][wsp.second].first=='s')
	{
		pl[map[wsp.first-1][wsp.second].second].set_or_check_max(happines);
		if(pl[map[wsp.first-1][wsp.second].second].max>best)
		{
			best3=best2;
			best2=best;
			best=pl[map[wsp.first-1][wsp.second].second].max;
		}
	}
	if(map[wsp.first][wsp.second-1].first=='p' || map[wsp.first][wsp.second-1].first=='s')
	{
		pl[map[wsp.first][wsp.second-1].second].set_or_check_max(happines);
		if(pl[map[wsp.first][wsp.second-1].second].max>best)
		{
			best3=best2;
			best2=best;
			best=pl[map[wsp.first][wsp.second-1].second].max;
		}
	}
}

std::pair<int,int> Person::move(std::vector<Plate> &pl,std::pair<char,int> **map)
{
	moved=true;
	if(map[wsp.first+1][wsp.second].first=='p' || map[wsp.first+1][wsp.second].first=='s')
	{
		if(pl[map[wsp.first+1][wsp.second].second].max==best && pl[map[wsp.first+1][wsp.second].second].is_free==1)
		{
			change_happines(2);
			return std::pair<int,int>(wsp.first+1,wsp.second);
		}
	}
	if(map[wsp.first][wsp.second+1].first=='p' || map[wsp.first][wsp.second+1].first=='s')
	{
		pl[map[wsp.first][wsp.second+1].second];
		if(pl[map[wsp.first][wsp.second+1].second].max==best && pl[map[wsp.first][wsp.second+1].second].is_free==1)
		{
			change_happines(2);
			return std::pair<int,int>(wsp.first,wsp.second+1);
		}
	}
	if(map[wsp.first-1][wsp.second].first=='p' || map[wsp.first-1][wsp.second].first=='s')
	{
		pl[map[wsp.first-1][wsp.second].second];
		if(pl[map[wsp.first-1][wsp.second].second].max==best && pl[map[wsp.first-1][wsp.second].second].is_free==1)
		{
			change_happines(2);
			return std::pair<int,int>(wsp.first-1,wsp.second);
		}
	}
	if(map[wsp.first][wsp.second-1].first=='p' || map[wsp.first][wsp.second-1].first=='s')
	{
		pl[map[wsp.first][wsp.second-1].second];
		if(pl[map[wsp.first][wsp.second-1].second].max==best && pl[map[wsp.first][wsp.second-1].second].is_free==1)
		{
			change_happines(2);
			return std::pair<int,int>(wsp.first,wsp.second-1);
		}
	}
	if(map[wsp.first+1][wsp.second].first=='p' || map[wsp.first+1][wsp.second].first=='s')
	{
		if(pl[map[wsp.first+1][wsp.second].second].max==best2 && pl[map[wsp.first+1][wsp.second].second].is_free==1)
		{
			change_happines(1);
			return std::pair<int,int>(wsp.first+1,wsp.second);
		}
	}
	if(map[wsp.first][wsp.second+1].first=='p' || map[wsp.first][wsp.second+1].first=='s')
	{
		pl[map[wsp.first][wsp.second+1].second];
		if(pl[map[wsp.first][wsp.second+1].second].max==best2 && pl[map[wsp.first][wsp.second+1].second].is_free==1)
		{
			change_happines(1);
			return std::pair<int,int>(wsp.first,wsp.second+1);
		}
	}
	if(map[wsp.first-1][wsp.second].first=='p' || map[wsp.first-1][wsp.second].first=='s')
	{
		pl[map[wsp.first-1][wsp.second].second];
		if(pl[map[wsp.first-1][wsp.second].second].max==best2 && pl[map[wsp.first-1][wsp.second].second].is_free==1)
		{
			change_happines(1);
			return std::pair<int,int>(wsp.first-1,wsp.second);
		}
	}
	if(map[wsp.first][wsp.second-1].first=='p' || map[wsp.first][wsp.second-1].first=='s')
	{
		pl[map[wsp.first][wsp.second-1].second];
		if(pl[map[wsp.first][wsp.second-1].second].max==best2 && pl[map[wsp.first][wsp.second-1].second].is_free==1)
		{
			change_happines(1);
			return std::pair<int,int>(wsp.first,wsp.second-1);
		}
	}
	if(map[wsp.first+1][wsp.second].first=='p' || map[wsp.first+1][wsp.second].first=='s')
	{
		if(pl[map[wsp.first+1][wsp.second].second].max==best3 && pl[map[wsp.first+1][wsp.second].second].is_free==1)
		{
			change_happines(1);
			return std::pair<int,int>(wsp.first+1,wsp.second);
		}
	}
	if(map[wsp.first][wsp.second+1].first=='p' || map[wsp.first][wsp.second+1].first=='s')
	{
		pl[map[wsp.first][wsp.second+1].second];
		if(pl[map[wsp.first][wsp.second+1].second].max==best3 && pl[map[wsp.first][wsp.second+1].second].is_free==1)
		{
			change_happines(1);
			return std::pair<int,int>(wsp.first,wsp.second+1);
		}
	}
	if(map[wsp.first-1][wsp.second].first=='p' || map[wsp.first-1][wsp.second].first=='s')
	{
		pl[map[wsp.first-1][wsp.second].second];
		if(pl[map[wsp.first-1][wsp.second].second].max==best3 && pl[map[wsp.first-1][wsp.second].second].is_free==1)
		{
			change_happines(1);
			return std::pair<int,int>(wsp.first-1,wsp.second);
		}
	}
	if(map[wsp.first][wsp.second-1].first=='p' || map[wsp.first][wsp.second-1].first=='s')
	{
		pl[map[wsp.first][wsp.second-1].second];
		if(pl[map[wsp.first][wsp.second-1].second].max==best3 && pl[map[wsp.first][wsp.second-1].second].is_free==1)
		{
			change_happines(1);
			return std::pair<int,int>(wsp.first,wsp.second-1);
		}
	}
	change_happines(-1);
	return wsp;
}

void Person::set_happines(const int &h)
{
	happines=h;
}

void Person::change_happines(const int &ch){
	if(happines+ch>0)
		happines+=ch;
}

void Person::end(const std::vector<Attractor> &atr)
{
	for(int i=0;i<atr.size();++i)
	{
		if(std::sqrt((wsp.first-atr[i].wsp.first)*(wsp.first-atr[i].wsp.first)+
				(wsp.second-atr[i].wsp.second)*(wsp.second-atr[i].wsp.second))<2)
			alive=false;
	}
}




					/* PLATE */

Plate::Plate(const std::pair<int,int> &pai, const bool _is_static, const int want):wsp(pai),val(want),max(0),is_free(1),is_static(_is_static){}

Plate::~Plate(){
}

void Plate::calculate_plate_value(const std::vector<Attractor> &atr)
{
	double po=0;
	for(unsigned int i=0;i<atr.size();++i)
	{
		if(po<(atr[i].power/std::sqrt((wsp.first-atr[i].wsp.first)*(wsp.first-atr[i].wsp.first)+(wsp.second-atr[i].wsp.second)*(wsp.second-atr[i].wsp.second))))
			po=atr[i].power/std::sqrt((wsp.first-atr[i].wsp.first)*(wsp.first-atr[i].wsp.first)+(wsp.second-atr[i].wsp.second)*(wsp.second-atr[i].wsp.second));
	}
	set_value(po);
}

void Plate::change_plate_value(const double &vl)
{
	if(val+vl>0 && is_static==false)
		val+=vl;
}

void Plate::set_value(const double &vl)
{
	val=vl;
}

void Plate::set_or_check_max(const double &m)
{
	if(m*val>max)
		max=m*val;
}



					/* WALL */

Wall::Wall(const std::pair<int,int> &pai):wsp(pai){}


					/* ATRAKTOR */

Attractor::Attractor(const std::pair<int,int> &pai, const unsigned int &p):power(p),wsp(pai){}

void Attractor::set_power(const int &p){
	power=p;
}



} /* namespace cnt */
