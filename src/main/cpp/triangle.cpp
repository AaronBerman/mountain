#include <iostream>
#include "triangle.h"
#include "side.h"

using namespace std;

triangle::triangle()
{
	a = side();
	b = side();
	c = side();
	Aptr = nullptr;
	Bptr = nullptr;
	Cptr = nullptr;
	point temp = point(0,0,0);
	center = temp;
	id = 0;
}
	
triangle::triangle(side one, side two, side three, int iD)
{
	a = one;
	b = two;
	c = three;
	Aptr = nullptr;
	Bptr = nullptr;
	Cptr = nullptr;
	id = iD;
	centroid();
}

triangle::triangle(point one, point two, point three, int iD)
{
	a = side(one, two);
	b = side(two, three);
	c = side(three, one);
	Aptr = nullptr;
	Bptr = nullptr;
	Cptr = nullptr;
	id = iD;
	centroid();
}

triangle::triangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, int iD)
{
	a = side(x1, y1, z1, x2, y2, z2);
	b = side(x2, y2, z2, x3, y3, z3);
	c = side(x3, y3, z3, x1, y1, z1);
	Aptr = nullptr;
	Bptr = nullptr;
	Cptr = nullptr;
	id = iD;
	centroid();
}

triangle::~triangle()
{

}

void triangle::centroid()
{
	double avgX, avgY, avgZ;

	avgX = (getA().getEndP1().getX() + getB().getEndP1().getX() + getC().getEndP1().getX()) / 3;
	avgY = (getA().getEndP1().getY() + getB().getEndP1().getY() + getC().getEndP1().getY()) / 3;
	avgZ = (getA().getEndP1().getZ() + getB().getEndP1().getZ() + getC().getEndP1().getZ()) / 3;

	point temp;
	temp = point(avgX, avgY, avgZ);
	center = temp;
}

void triangle::display(std::ostream &outs) const
{
	a.display(outs);
	c.display(outs);
	outs << endl;
	outs << endl;
};