
#include <iostream>
#include <list>
#include <stdlib.h>
#include <windows.h>
using namespace std;

//define a new class Point


class Point{
	private:
		int x = 0;
		int y = 0;
		Point *p; 	//px,py : parent's x,y
		
		int g = 0;
		int h = 0;

		bool passed = false;
		bool blocked = false;
		
	public:
		Point(){}
		//Point initialise(int arr[][]){
		//}
		void setPoint(int a, int b) { x = a; y = b; }
		void setParent(Point pp) { p = &pp; }
		void setG() {; }
		void setH() { h = (4 - x) + (4 - y); }

		void setBlocked() { blocked = true; ;
		}
		void setPassed() { passed = true; }
		void unSetPassed() { passed = false; }

		//calculate distance (p->start)
		int getDistance(Point *p) {
			if (getX() != 0 || getY() != 0) {
				return getDistance(getP()) + 1;
			}
			else { return 0; }
		}

		//distance p->start (through parents) 
		int getG() {
			return g;
		}

		//distance p->end (by width + height)
		int getH() {
			return h;
		}

		//f(x) = g(x) + h(x)
		int getF() {
			return (g + h);
		}

		int getX() { return x; }
		int getY() { return y; }
		Point *getP() { return p; }
		//int getPY(Point p) { return py; }

		bool isBlocked() { return blocked; }
		bool isPassed() { return passed; }


};


//find the minimun f() Point
Point min_p(list<Point> l){
	Point minP;
	int minValue=0;

	for (list<Point>::iterator it = l.begin(); it != l.end(); it++){
		int temp = (*it).getF();
    		if( temp < minValue){
    			minValue = temp;
    			minP = *it;
    		}
    	}
    return minP;
}

//void print(Point);
void searchAround(int, int);

int main(){

	//define two list
	list<Point> openList;
	list<Point> closeList;
	
	Point map[7][7];

	int nowX = 0;
	int nowY = 0;	
	
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			map[i][j].setPoint(i, j);
			//map[i][j].setParent(0, 0);
			map[i][j].setH();
		}
	}
	openList.push_back(map[1][1]);      // X X X X X X X
	closeList.push_back(map[2][1]);     // X S 0 0 0 0 X
	closeList.push_back(map[2][2]);     // X 1 1 1 0 1 X
	closeList.push_back(map[2][3]);		// X 0 0 0 0 0 X
	closeList.push_back(map[2][5]);		// X 0 1 0 1 1 X
	closeList.push_back(map[4][2]);		// X 0 1 0 0 E X
	closeList.push_back(map[4][4]);		// X X X X X X X
	closeList.push_back(map[4][5]);
	closeList.push_back(map[5][2]);
	map[2][1].setBlocked();
	map[2][2].setBlocked();
	map[2][3].setBlocked();
	map[2][5].setBlocked();
	map[4][2].setBlocked();
	map[4][4].setBlocked();
	map[4][5].setBlocked();
	map[5][2].setBlocked();
	////////////////////////////Make Outside Blocked
	for (int i =0; i < 7; i++) {
		for (int j= 0; j < 7; j++) {
			if (i == 0 || i == 6 || j == 0 || j == 6) {
				map[i][j].setBlocked();
				closeList.push_back(map[i][j]);
			}
		}
	}
	
	while ((openList.empty()) || !(nowX == 4 && nowY == 4)) {
		
		Point tempPoint = min_p(openList);
		//add the minimun f() element into closeList
		
		int absX = abs(tempPoint.getX() - nowX);
		int absY = abs(tempPoint.getY() - nowY);

		map[nowX][nowY].setPassed();

		if (absX >1 && absY >1) {
			nowX = (*(map[nowX][nowY].getP())).getX();
			nowY = (*(map[nowX][nowY].getP())).getY();
		}

		closeList.push_back(map[tempPoint.getX()][tempPoint.getY()]);
		map[tempPoint.getX()][tempPoint.getY()].setBlocked();
		
		//delete the element from openList	
		//openList.erase(map[tempPoint.getX()][tempPoint.getY()]);
		nowX = tempPoint.getX();
		nowY = tempPoint.getY();
		//searchAround(nowX, nowY);


		//searchAround and add to openList
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (map[nowX +i][nowY + j].isBlocked()==false || map[nowX + i][nowY + j].isPassed() ==false) {
					openList.push_back(map[nowX + i][nowY + i]);
				}
			}
		}


		////Print
		cout << "Map : \n";
		for (int i = 1; i < 6; i++) {
			for (int j = 1; j < 6; j++) {
				if (nowX == i && nowY == j) { cout << "@ "; continue; }
				if (map[i][j].isBlocked()) { cout << "x "; continue; }
				if (map[i][j].isPassed()) { cout << "o "; continue; }
				
				cout << "- ";

			}
			cout << "\n";
		}

		for (int i = 1; i < 6; i++) {
			for (int j = 1; j < 6; j++) {
				cout << map[i][j].isPassed() << " ";


			}
			cout << "\n";
		}

		////
  		cout << '\n';
		Sleep(2000);

  	}

	return 0;
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