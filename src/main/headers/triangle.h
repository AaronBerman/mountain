#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include "point.h"
#include "side.h"

class triangle
{
public:
	triangle();
	triangle(side one, side two, side three,int iD);
	triangle(point one, point two, point three, int iD);
	triangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, int iD);
	virtual ~triangle();

	void centroid();
	side getA() {return a;}
	triangle* getAptr() {return Aptr;}
	side getB() {return b;}
	triangle* getBptr() {return Bptr;}
	side getC() {return c;}
	triangle* getCptr() {return Cptr;}
	int getId() {return id;}

	point getCenter() {return center;}

	void setA(side newSide) {a = newSide;}
	void setAptr(triangle *nextTriangle) {Aptr = nextTriangle;}
	void setB(side newSide) {a = newSide;}
	void setBptr(triangle *nextTriangle) {Bptr = nextTriangle;}
	void setC(side newSide) {a = newSide;}
	void setCptr(triangle *nextTriangle) {Cptr = nextTriangle;}
	void setCenter(point newPoint) {center = newPoint;}
	void setId(int x) { id = x;}

	void display(std::ostream &outs) const;

private:
	side a;
	triangle *Aptr;
	side b;
	triangle *Bptr;
	side c;
	triangle *Cptr;
	point center;
	int id;
};

#endif