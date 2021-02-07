/*
 * Aaron Berman CS 361
 */

#include <iostream>
#include <random>
#include <ctime>
#include <list>
#include <queue>
#include <fstream>
#include <math.h>

#include "main.h"
#include "triangle.h"
#include "point.h"

using namespace std;

void refine(triangle current, default_random_engine *generatorPointer, int age, list<triangle>& mountainList, int iD);

int main (int argc, char** argv) 
{   
	int xPeak, yPeak, refineTimes, idNumber;
	list<triangle> mountainList;
    list<triangle>::iterator mitr;
    triangle *onePtr, *twoPtr, *threePtr, *fourPtr;

    cout << "Welcome to the Mountain.\n" << "We will generate a mountain with a base of 200x200." << endl;
    cout << "Next, we need a peak height: recommended heights are 300 < height < 600 with a max of 750." << endl;

    int height = -1;
    while ((height <= 0) || (height > 750))
    {
    	cout << "what is the peak height [0-750]? "; 
    	cin >> height;
    }

    int age = 0;
    while ((age > 5) || (age < 1))
    {
    	cout << "Choose a number [1-5] 1 being old and 5 being young for the mountain: [1-5]" << endl;
    	cin >> age;
    }

    refineTimes = -1;
    while ((refineTimes <= 0 ) || (refineTimes > 100))
    {
    	cout << "Choose a number of times to refine the triangles 0 - 100" << endl;
    	cin >> refineTimes;
    }

    //This creates the basis of the true random generation
    default_random_engine *generatorPointer;
    generatorPointer = new default_random_engine(time(NULL));

	//peak xy random generation
	normal_distribution<double> xyPeak(500.0, 150.0);

    //create the base of the mountain with points
    point A = point(0, 0, 0);
    point B = point(1000, 0, 0);
    point C = point (1000, 1000, 0);
    point D = point(0, 1000 , 0);

    //create the point for the peak
    xPeak = int(xyPeak(*generatorPointer) );
    yPeak = int(xyPeak(*generatorPointer) );
    point P = point (xPeak, yPeak, height);

    //create the edges from the points
    side A1 = side(A, B);
    side A2 = side(B, P);
    side A3 = side(P, A);
    side B1 = side(B, C);
    side B2 = side(C, P);
    side B3 = side(P, B);
    side C1 = side(C, D);
    side C2 = side(D, P);
    side C3 = side(P, C);
    side D1 = side(D, A);
    side D2 = side(A, P);
    side D3 = side(P, D);
   idNumber = 0;
    //create the intitial triangles
    onePtr = new triangle(A1,A2,A3,idNumber);
	idNumber++;
    mountainList.push_back(*onePtr);
    twoPtr = new triangle(B1,B2,B3,idNumber);
    idNumber++;
    mountainList.push_back(*twoPtr);
    threePtr = new triangle(C1,C2,C3,idNumber);
    idNumber++;
    mountainList.push_back(*threePtr);
    fourPtr = new triangle(D1,D2,D3,idNumber);
    idNumber++;
    mountainList.push_back(*fourPtr);
        
    mitr = mountainList.begin();
    onePtr = &(*mitr);
    mitr++;
    twoPtr = &(*mitr);
    mitr++;
    threePtr = &(*mitr);
    mitr++;
    fourPtr = &(*mitr);

    mitr = mountainList.begin();
    mitr->setAptr(nullptr);
    mitr->setBptr(twoPtr);
    mitr->setCptr(fourPtr);
    mitr++;
    mitr->setAptr(nullptr);
    mitr->setBptr(threePtr);
    mitr->setCptr(onePtr);
    mitr++;
    mitr->setAptr(nullptr);
    mitr->setBptr(fourPtr);
    mitr->setCptr(twoPtr);
    mitr++;
    mitr->setAptr(nullptr);
    mitr->setBptr(onePtr);
    mitr->setCptr(threePtr);

    /*initalization of the list is done
    *now we have to get the centroid
	*adjust the centroid of the triangle to age
	*then refine the triangle  
     */
     mitr = mountainList.begin();
    for(int i = 0; i < refineTimes; i++) 
    {
    	if (mitr->getA().getEndP1().getZ() + mitr->getC().getEndP1().getZ() > 10) {
    		if (mitr->getA().getEndP1().getX() + mitr->getC().getEndP1().getX() > 10) {
    			if (mitr->getA().getEndP1().getY() + mitr->getC().getEndP1().getY() > 10) {
    				refine(*mitr, generatorPointer, age, mountainList, idNumber);
    				mitr = mountainList.erase(mitr);
    				idNumber = idNumber + 3;
    			}
    		}
    	}
    	else {
    		mitr++;
    	}
    }	
   
    fstream outs;
    //should build the triangle file of the whole mountain for GNU plot
    outs.open("mountain.txt", ios::out);
    mitr = mountainList.begin();
    while (mitr != mountainList.end()){
    	mitr->display(outs);
    	mitr++;
    }
    outs.close();

    //use dijkstras algroithm to get the path in a priority queue



    //should build the triangle file of the mountain path for GNU plot
    outs.open("mountainPath.txt", ios::out);
     mitr = mountainList.begin();
    while (mitr != mountainList.end()){
    	mitr->display(outs);
    	mitr++;
    }
    outs.close();

 	//command.txt creation for GNU plot
    outs.open("command.txt", ios::out);
    outs << "set size 1,1" << endl;
    outs << "set xlabel \"x distance in km\"" << endl;
    outs << "set ylabel \"y distance in km\"" << endl;
    outs << "set zlabel \"z altitude in km\"" <<endl;

    outs << "set xrange [-25:1025]" << endl;
    outs << "set yrange [-25:1025]" << endl;
    outs << "set zrange [0:800]" << endl;
    outs << "set xyplane relative 0" << endl;
    outs << "set view equal xyz" << endl;

    outs << "splot \"mountain.txt\"  with lines " << endl;
    //outs << "\"mountainPath.txt\"  with lines" << endl;

    outs << "pause -1";
    outs.close();
    
    system("gnuplot command.txt");
    return 0;
}

void refine(triangle current, default_random_engine *generatorPointer, int age, list<triangle>& mountainList, int iD){

	point centr = current.getCenter();

	//centroid random movement generation
    uniform_int_distribution<int> adjustXYCentroid(0,age*10);
    uniform_int_distribution<int> adjustZCentroid(0, age*40);

	centr.setX(centr.getX() + adjustXYCentroid(*generatorPointer));
	centr.setY(centr.getY() + adjustXYCentroid(*generatorPointer));
	centr.setZ(centr.getZ() + adjustZCentroid(*generatorPointer));

	triangle *aTri, *bTri, *cTri;
	side A1 = side(current.getA().getEndP1(), current.getB().getEndP1());
    side A2 = side(current.getB().getEndP1(), centr);
    side A3 = side(centr, current.getA().getEndP1());
    side B1 = side(current.getB().getEndP1(), current.getC().getEndP1());
    side B2 = side(current.getC().getEndP1(), centr);
    side B3 = side(centr, current.getB().getEndP1());
    side C1 = side(current.getC().getEndP1(), current.getA().getEndP1());
    side C2 = side(current.getA().getEndP1(), centr);
    side C3 = side(centr, current.getC().getEndP1());
    
    aTri = new triangle(A1, A2, A3, iD);
    iD++;
    bTri = new triangle(B1, B2, B3, iD);
    iD++;
    cTri = new triangle(C1, C2, C3,iD);

aTri->setAptr(current.getAptr());

    aTri->setBptr(bTri);
    aTri->setCptr(cTri);
    bTri->setAptr(aTri);
    bTri->setBptr(current.getBptr());
    bTri->setCptr(cTri);
    cTri->setAptr(aTri);
    cTri->setBptr(bTri);
    cTri->setCptr(current.getCptr());
 
    //set the what the original triangle was pointing to to point at the child triangle
    list<triangle>::iterator checkMountain;
    triangle *theChange;
    triangle *toRemove;
    checkMountain = mountainList.begin();
    toRemove = &(*mountainList.begin());
    checkMountain++;

    while(checkMountain != mountainList.end()){
    	triangle *atemp;
    	triangle *btemp;
    	triangle *ctemp;
    	theChange = &(*checkMountain);
    	atemp = checkMountain->getAptr();
    	btemp = checkMountain->getBptr();
		ctemp = checkMountain->getCptr();

    	if (atemp != nullptr ){
    		if (atemp == toRemove){
    			theChange->setAptr(aTri);
    		}
    	}	
    	if (btemp != nullptr){
     		if (btemp == toRemove){
    			theChange->setBptr(cTri);
    		}
        }
    	if (ctemp != nullptr){
    		if (ctemp == toRemove){
    			theChange->setCptr(bTri);
    		}
    	}
 
    checkMountain++;
    }

    //Add child triangles to list
    mountainList.push_back(*aTri);
    mountainList.push_back(*bTri);
    mountainList.push_back(*cTri);
  
}