#ifndef SIDE_H
#define SIDE_H

#include <iostream>
#include "point.h"

class side
{
public:
	side();
	side(point a, point b);
	side(double X1, double Y1, double Z1, double X2, double Y2, double Z2);
	virtual ~side();

	point getEndP1(){return one;}
	point getEndP2(){return two;}
	
	void setEndP1(point a) { one = a;}
	void setEndP2(point b) { two = b;}

	void display(std::ostream &outs) const;

private:
	point one;
	point two;	
};
#endif