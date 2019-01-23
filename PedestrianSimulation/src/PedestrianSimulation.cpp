#include <iostream>
#include "Floor.h"

int main(int argc, char **argv)
{
	std::pair<std::string,std::string> pa;
	pa.first="test";
	pa.second="testex";
	Floor aa(pa);
	aa.move_x_step(1001);
	std::cout<<"end"<<std::endl;
}
