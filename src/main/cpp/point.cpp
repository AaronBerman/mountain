#include <iostream>
#include "point.h"

using namespace std;

point::point()
{
	x = 0;
	y = 0;
	z = 0;
}

point::point(double a, double b)
{
	x = a;
	y = b;
	z = 0;
}

point::point(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}

point::~point()
{

}

void point::display(std::ostream &outs) const
{
	outs << x << " " << y << " " << z ;
}