#ifndef COTAINERS_H_
#define COTAINERS_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>


namespace cnt {

class Person;
class Plate;
class Wall;
class Attractor;

class Person {
public:

	std::pair<int,int> wsp;
	double happines;
	bool alive,moved;
	double best,best2,best3;

	Person(const std::pair<int,int> &pai,const double &happy=5);
	virtual ~Person(){};

	const std::pair<int,int>& move();									//poruszanie sie
	void set_happines(const int &h);
	void set_pref(std::vector<Plate> &pl,std::pair<char,int> **map);
	void change_happines(const int &ch);
	std::pair<int,int> move(std::vector<Plate> &pl,std::pair<char,int> **map);
	void end(const std::vector<Attractor> &atr);

};


class Plate {
public:
	const std::pair<int,int> wsp;
	double val;
	double max;
	bool is_free;
	const bool is_static;

	Plate(const std::pair<int,int> &pai, const bool _is_static = false, const int want=6);
	virtual ~Plate();

	void calculate_plate_value(const std::vector<Attractor> &atr);
	void set_value(const double &vl);
	void change_plate_value(const double &vl);
	void set_or_check_max(const double &m);

};

class Wall {
public:
	const std::pair<int,int> &wsp;

	Wall(const std::pair<int,int> &pai);
	virtual ~Wall(){};
};

class Attractor {
public:
	int power;
	std::pair<int,int> wsp;

	Attractor(const std::pair<int,int> &pai, const unsigned int &p = 100);
	virtual ~Attractor(){};

	void set_power(const int &p);

};

} /* namespace cnt */

#endif /* COTAINERS_H_ */
