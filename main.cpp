
#include <iostream>
#include <list>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

//define a new class Point		
class Point{
	private:
		int x = 0;
		int y = 0;		
		int g = 0;
		int h = 0;

		Point *p; 	//p: pointer to parent 

		bool passed = false;
		bool blocked = false;
		
	public:
		Point();
		Point(int, int);
		//Point initialise(int arr[][]){}
		void setPoint(int , int );
		void setParent(Point );
		void setG();
		void setH();
		void setBlocked();
		void setPassed();
		void unSetPassed();		//we will use when we track back
		
		int getDistance(Point ); //calculate distance (p->start)		
		int getG(); //distance p->start (through parents) 		
		int getH(); //distance p->end (by width + height)		
		int getF(); //f(x) = g(x) + h(x)
		int getX();
		int getY();

		Point *getP();
		//int getPY(Point p) { return py; }

		bool isBlocked();
		bool isPassed();

};

//find the minimun f() among Points in the openList
Point* min_p(list<Point*> l);
//void print();
void searchAround(int, int);

int main(){

	//define two list
	list<Point*> openList;
	list<Point*> closeList;
	list<Point*>::iterator iter;
	iter = openList.begin();
	
	//Point* mapA= new Point();
	Point* map[7][7];

	int nowX = 1;
	int nowY = 1;	
	
	//initialize
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
	
			map[i][j] = new Point(i, j);
			map[i][j]->setH();
		}
	}

										//		MAP
	openList.push_back(map[1][1]);      // X X X X X X X		S: start
	closeList.push_back(map[2][1]);     // X S 0 0 0 0 X		E: end
	closeList.push_back(map[2][2]);     // X 1 1 1 0 1 X		X: outside (I made it for searchAround easily and for unifying searchAround function.)
	closeList.push_back(map[2][3]);		// X 0 0 0 0 0 X		1: blocked
	closeList.push_back(map[2][5]);		// X 0 1 0 1 1 X		0: way
	closeList.push_back(map[4][2]);		// X 0 1 0 0 E X
	closeList.push_back(map[4][4]);		// X X X X X X X		//I changed this map a little for verification of suitability of algorithm more efficiently.
	closeList.push_back(map[4][5]);
	closeList.push_back(map[5][2]);
	(*map[2][1]).setBlocked();
	(*map[2][2]).setBlocked();
	(*map[2][3]).setBlocked();
	(*map[2][5]).setBlocked();
	(*map[4][2]).setBlocked();
	(*map[4][4]).setBlocked();
	(*map[4][5]).setBlocked();
	(*map[5][2]).setBlocked();
	////////////////////////////Make Outside Blocked
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (i == 0 || i == 6 || j == 0 || j == 6) {
				(*map[i][j]).setBlocked();
				closeList.push_back(map[i][j]);
			}
		}
	}

	////Print 
	cout << "Map : Start \n";
	for (int i = 1; i < 6; i++) {
		for (int j = 1; j < 6; j++) {
			if (nowX == i && nowY == j) { cout << "! "; continue; }
			if ((*map[i][j]).isBlocked()) { cout << "x "; continue; }
			if ((*map[i][j]).isPassed()) { cout << "o "; continue; }

			cout << "- ";

		}
		cout << "\n";
	}

	/*
	///////// Example :::::::::::push,remove and iterator USAGE
	openList.push_back(map[2][1]);
	openList.remove(map[1][1]);
	for (list<Point*>::iterator iter = openList.begin(); iter != openList.end(); iter++)
	{
		cout << (*iter)->getX() <<endl;
	}
	cout << "openList Size : " << openList.size() << "\n";
	
	*/

	
	while ((openList.empty()) || !(nowX == 5 && nowY == 5)) {
		
		Point* tempPoint = min_p(openList);
		//add the minimun f() element into closeList
		
		int absX = abs((*tempPoint).getX() - nowX);
		int absY = abs((*tempPoint).getY() - nowY);

		(*map[nowX][nowY]).setPassed();

		if (absX >1 && absY >1) {
			nowX = (*(*map[nowX][nowY]).getP()).getX();
			nowY = (*(*map[nowX][nowY]).getP()).getY();
		}

		closeList.push_back(map[(*tempPoint).getX()][(*tempPoint).getY()]);
		(*map[(*tempPoint).getX()][(*tempPoint).getY()]).setBlocked();
		
		//delete the element from openList	
		//openList.erase(map[tempPoint.getX()][tempPoint.getY()]);
		nowX = (*tempPoint).getX();
		nowY = (*tempPoint).getY();
		//searchAround(nowX, nowY);


		//searchAround and add to openList
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if ((*map[nowX +i][nowY + j]).isBlocked()==false || (*map[nowX + i][nowY + j]).isPassed() ==false) {
					openList.push_back(map[nowX + i][nowY + i]);
				}
			}
		}

		////Print
		cout << "Map : \n";
		for (int i = 1; i < 6; i++) {
			for (int j = 1; j < 6; j++) {
				if (nowX == i && nowY == j) { cout << "! "; continue; }
				if ((*map[i][j]).isBlocked()) { cout << "x "; continue; }
				if ((*map[i][j]).isPassed()) { cout << "o "; continue; }
				
				cout << "- ";

			}
			cout << "\n";
		}

		//test
		cout << " now :" << nowX << ", " << nowY <<"\n";

		cout << "Passed check : \n";
		for (int i = 1; i < 6; i++) {
			for (int j = 1; j < 6; j++) {
				cout << (*map[i][j]).isPassed() << " ";

			}
			cout << "\n";
		}

		////
  		cout << '\n';
		Sleep(2000);

  	}
	
	return 0;
}

Point::Point() { setPoint(0, 0); g = 0; h = 0; passed = false; blocked = false; }
Point::Point(int xx, int yy) { setPoint(xx, yy); g = 0; h = 0; passed = false; blocked = false;}
//Point initialise(int arr[][]){}

void Point::setPoint(int a, int b) { x = a; y = b; }
void Point::setParent(Point pp) { p = &pp; }
void Point::setG() { ; }
void Point::setH() { h = (5 - x) + (5 - y); }

void Point::setBlocked() {blocked = true;}
void Point::setPassed() { passed = true; }
void Point::unSetPassed() { passed = false; }

int Point::getG() {return g;}	//distance p->start (through parents) 
int Point::getH() {return h;} //distance p->end (by width + height)
int Point::getF() {return (g + h);} //f(x) = g(x) + h(x)
int Point::getX() {return x;}
int Point::getY() {return y;}
Point* Point::getP() { return p; }
//int getPY(Point p) { return py; }

//calculate distance (p->start) by passed path
int Point::getDistance(Point p) {
	if (getX() != 0 || getY() != 0) {
		return getDistance( *(p.getP()) ) + 1;
	}
	else { return 0; }
}

bool Point::isBlocked() { return blocked; }
bool Point::isPassed() { return passed; }


Point* min_p(list<Point*> l) {
	Point* minP = *(l.begin());
	int minValue = 0;

	for (list<Point*>::iterator it = l.begin(); it != l.end(); it++) {
		int temp = (*it)->getF();
		if (temp < minValue) {
			minValue = temp;
			minP = *it;
		}
	}
	return minP;
}


//failed to implement outside of main() independantly. T-T
/*
void searchAround(int x, int y) {
	Point temp =(Point)map[x-1][y-1]
}
*/
//failed to implement outside of main() independantly. T-T
/*
void print(Point* map) {
	cout << "Map : \n";
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (map[i][j].getBlocked()) { cout << "x "; continue; }
			if (map[i][j].getPassed()) { cout << "o "; continue; }
			cout << "- ";

		}
		cout << "\n";
	}
}*/