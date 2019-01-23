#ifndef BUILDER_H_
#define BUILDER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>

class Builder{
	int row;
	int col;
	char **tab;
	std::string name;
public:
	Builder(const int & _i, const int & _j);
	Builder();
	std::pair<const std::string,const std::string> command_build();
	std::string command_build_ext(std::string name,const int &h,const int &p,const int &a);

	virtual ~Builder();

private:
	void _add_human(const int &a, const int &b);
	void _add_wall(const int &a, const int &b);
	void _add_plate(const int &a, const int &b);
	void _add_static_plate(const int &a, const int &b);
	void _add_atractor(const int &a, const int &b);

	void _print_commands();
	void _print_commands_ext();
	void _check(const std::stringstream &s);
	void _show();

};

struct outside_of_floor
{
	const unsigned int a,b;
	outside_of_floor(const unsigned int &_a, const unsigned int &_b):a(_a),b(_b){}
};
struct not_enought_arguments{
	not_enought_arguments()=default;
};

#endif
