#ifndef FLOOR_H_
#define FLOOR_H_

#include <vector>
#include <utility>
#include <fstream>

//#include <thread>

#include "Builder.h"
#include "Cotainers.h"
//#include "Interpreter.h"	// interpreter bmp



#define Epsilon 0.001

class IFloor;
class Floor;
class Interpreter;
class Observer;

class IFloor{
public:
	virtual void move_x_step(const unsigned int &st_numb)=0;
	virtual void move_untill_end()=0;
	virtual ~IFloor(){}
private:
	virtual void _calculate()=0;
	virtual void _move(char &change)=0;
	virtual void _move_person(const std::pair<int,int> &p, const std::pair<int,int> &k,std::vector<cnt::Person>::iterator &it)=0;
	virtual void _load(const std::pair<const std::string,const std::string> &name)=0;
	virtual void _build_map(const int &a, const int &b)=0;
	virtual void _build_human_map(const int &a, const int &b)=0;
	virtual void _save(const std::string &name_out="Result")const =0;
	virtual void _kill()=0;
	virtual std::pair<const std::string,const std::string> _build_floor(const int &row,const int &col)=0;
};

class Floor : public IFloor{
	std::vector<cnt::Person> ludzie;
	std::vector<cnt::Plate> plytki;
	std::vector<cnt::Wall> sciany;
	std::vector<cnt::Attractor> atraktory;

	std::pair<char,int> **mapa;
	std::pair<int,int> si;
	int **map_p;

	friend class Interpreter;
	friend class Observer;

public:
	Floor();
	Floor(const int &a, const int &b);
	Floor(const std::pair<const std::string,const std::string> &name);

	virtual void move_x_step(const unsigned int &st_numb) override;
	virtual void move_untill_end() override;

	virtual ~Floor();

private:
	virtual void _calculate() override;
	virtual void _move(char &change) override;
	virtual void _move_person(const std::pair<int,int> &p, const std::pair<int,int> &k,std::vector<cnt::Person>::iterator &it)override;
	virtual void _load(const std::pair<const std::string,const std::string> &name) override;
	virtual void _build_map(const int &a, const int &b) override;
	virtual void _build_human_map(const int &a, const int &b) override;
	virtual void _save(const std::string &name_out="Result")const override;
	virtual void _kill() override;
	virtual std::pair<const std::string,const std::string> _build_floor(const int &row = 0,const int &col = 0) override;

};

class Interpreter{
	Floor *const fp;
public:
	Interpreter(Floor *const p):fp(p){}
	~Interpreter() =default;
	void read(const std::string &name);
	void read_additional(const std::string &name);

private:
	void _check(const std::stringstream &s)const;
	void _add_plate(const unsigned int &i, const unsigned int &j,const bool is_static=false);
	void _add_s_plate(const unsigned int &i, const unsigned int &j);
	void _add_wall(const unsigned int &i, const unsigned int &j);
	void _add_human(const unsigned int &i, const unsigned int &j);
	void _add_attractor(const unsigned int &i, const unsigned int &j);

	void _set_plate_value(const unsigned int &i, const unsigned int &j);
	void _set_human_happines(const unsigned int &i, const unsigned int &j);
	void _set_attractor_power(const unsigned int &i, const unsigned int &j);

};

class Observer{
	const Floor &fr;
	std::ofstream plik;
public:
	Observer()=delete;
	Observer(const Floor &p);
	void write();
	void final();

	virtual ~Observer()=default;
};

struct not_open
{
	const std::string arg;
	not_open(const std::string &_arg):arg(_arg){};
};

struct symbol_is_not_in_base
{
	const char arg;
	symbol_is_not_in_base(const char &_arg):arg(_arg){};
};

#endif /* FLOOR_H_ */
