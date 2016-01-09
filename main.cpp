
#include <iostream>
#include <list>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

int objectX = 5;
int objectY = 5;

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
		void setG(Point);
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
//void searchAround(int , int , list<Point*> , Point* );

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
	closeList.push_back(map[4][4]);		// X X X X X X X		//changed this map a little for verification of suitability of algorithm more efficiently.
	closeList.push_back(map[4][5]);								//caution! : can move diagonally
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

	/*-----Example ::::::push,remove and iterator USAGE
	openList.push_back(map[2][1]);
	openList.remove(map[1][1]);
	for (list<Point*>::iterator iter = openList.begin(); iter != openList.end(); iter++)
	{
		cout << (*iter)->getX() <<endl;
	}
	cout << "openList Size : " << openList.size() << "\n";
	//---------------------------------------------------------------*/

	/*-----Check ::::::whether min_p works rightly. It works rightly.
	openList.push_back(map[2][1]);
	openList.push_back(map[4][2]);
	Point* tempPoint = min_p(openList);
	cout << "("<< tempPoint->getX() <<", "<< tempPoint->getY()<< ")\n";
	cout << "openList Size : " << openList.size() << "\n";
	//---------------------------------------------------------------*/

	
	while ((openList.empty()) || !(nowX == objectX && nowY==objectY) ) {

		Point* tempPoint = min_p(openList);	

		closeList.push_back(map[nowX][nowY]);
		openList.remove(map[nowX][nowY]);
		(*map[nowX][nowY]).setPassed();
		
		//openList.remove(map[(*tempPoint).getX()][(*tempPoint).getY()]);
		
		nowX = (*tempPoint).getX();
		nowY = (*tempPoint).getY();

		//searchAround(nowX, nowY,openList,map);
		//searchAround and add to openList
		
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (!((*map[nowX + i][nowY + j]).isBlocked() == true || (*map[nowX + i][nowY + j]).isPassed() == true) ) {
					bool exist = false;
					for (list<Point*>::iterator iter = openList.begin(); iter != openList.end(); iter++)					{
						if (map[nowX + i][nowY + j] == map[(*iter)->getX()][(*iter)->getY()]) {
							exist = true;
						}
					}
					if (exist == false)
					{ openList.push_back(map[nowX + i][nowY + j]); }
				}
			}
		}

		/*int absX = abs((*tempPoint).getX() - nowX);
		int absY = abs((*tempPoint).getY() - nowY);*/

		/*if (absX >1 && absY >1) {
			nowX = (*(*map[nowX][nowY]).getP()).getX();
			nowY = (*(*map[nowX][nowY]).getP()).getY();
		}*/

		//(*map[(*tempPoint).getX()][(*tempPoint).getY()]).setBlocked();
		


		//Print
		cout << "Map ::now (" << nowX << ", " << nowY <<")\n";
		for (int i = 1; i < 6; i++) {
			for (int j = 1; j < 6; j++) {
				if (nowX == i && nowY == j) { cout << "! "; continue; }
				if ((*map[i][j]).isBlocked()) { cout << "x "; continue; }
				if ((*map[i][j]).isPassed()) { cout << "o "; continue; }
				
				cout << "- ";

			}
			cout << "\n";
		}

		cout << "openList : ";
		for (list<Point*>::iterator iter = openList.begin(); iter != openList.end(); iter++)
		{
			cout << " (" << (*iter)->getX() <<", "<<(*iter)->getY()<<") ";
		}
		cout << "\n\n";


		//for checking passed()
		cout << "Passed check : \n";
		for (int i = 1; i < 6; i++) {
			for (int j = 1; j < 6; j++) {
				cout << (*map[i][j]).isPassed() << " ";

			}
			cout << "\n";
		}
		////

  		cout << "-----------------------------------------------------------------------------------\n";
		Sleep(2000);

  	}
	cout << "Finished!\n";
	return 0;
}

Point::Point() { setPoint(0, 0); g = 0; h = 0;}
Point::Point(int xx, int yy) { setPoint(xx, yy); g = 0; h = 0;}
//Point initialise(int arr[][]){}

void Point::setPoint(int a, int b) { x = a; y = b; }
void Point::setParent(Point pp) { p = &pp; }
void Point::setG(Point p) { g =getDistance(p); }
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
		if (minValue < temp) {
			temp = minValue;
			minP = *it;
		}
	}
	return minP;
}


//failed to implement outside of main() independantly. T-T

/*
void searchAround(int x, int y, list<Point*> l, Point* map) {
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (!((*map[x + i][y + j]).isBlocked() == true || (*map[x + i][y + j]).isPassed() == true)) {
				bool exist = false;
				for (list<Point*>::iterator iter = l.begin(); iter != l.end(); iter++) {
					if (map[x + i][y + j] == map[(*iter)->getX()][(*iter)->getY()]) {
						exist = true;
					}
				}
				if (exist == false)
				{
					l.push_back(map[x + i][y + j]);
				}
			}
		}
	};
}*/

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