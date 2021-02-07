#ifndef POINT_H
#define POINT_H

#include <iostream>

class point
{
public:
	point();
	point(double a, double b);
	point(double a, double b, double c);
	virtual ~point();

	double getX(){return x;}
	double getY(){return y;}
	double getZ(){return z;}

	void setX(double a) { x = a;}
	void setY(double b) { y = b;}
	void setZ(double c) { z = c;}

	void display(std::ostream &outs) const;

private:
	double x;
	double y;
	double z;
	
};
#endif
