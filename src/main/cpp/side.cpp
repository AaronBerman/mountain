#include <iostream>
#include "side.h"
#include "point.h"

using namespace std;

side::side()
{
	one = point();
	two = point();
}
	
side::side(point a, point b)
{
	one = a;
	two = b;
}

side::side(double X1, double Y1, double Z1, double X2, double Y2, double Z2)
{
	one = point(X1, Y1, Z1);
	two = point(X2, Y2, Z2);
}

side::~side()
{

}
	
void side::display(std::ostream &outs) const
{
	one.display(outs);
	outs << endl;
	two.display(outs);
	outs << endl;
}