
#include <iostream>
#include <list>
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

		void setBlocked() { blocked = true; }
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

		bool getBlocked() { return blocked; }
		bool getPassed() { return passed; }


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


int main(){

	//define two list
	list<Point> openList;
	list<Point> closeList;
	Point map[5][5];

	int nowX = 0;
	int nowY = 0;
	
	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			map[i][j].setPoint(i, j);
			//map[i][j].setParent(0, 0);
			map[i][j].setH();
		}
	}
	openList.push_back(map[0][0]);     //   S 0 0 0 0
	closeList.push_back(map[1][0]);    //   1 1 0 1 1
	closeList.push_back(map[1][1]);    //   0 0 0 0 0
	closeList.push_back(map[1][3]);    //   0 1 0 1 1
	closeList.push_back(map[1][4]);    //   0 1 0 0 E
	closeList.push_back(map[3][1]);
	closeList.push_back(map[3][3]);
	closeList.push_back(map[3][4]);
	closeList.push_back(map[4][1]);
	map[1][0].setBlocked();
	map[1][1].setBlocked();
	map[1][3].setBlocked();
	map[1][4].setBlocked();
	map[3][1].setBlocked();
	map[3][3].setBlocked();
	map[3][4].setBlocked();
	map[4][1].setBlocked();


	
	while ((openList.empty()) || (nowX == 4 && nowY == 4)) {
		
		Point tempPoint = min_p(openList);
		//add the minimun f() element into closeList
		closeList.push_back(tempPoint);
		//delete the element from openList	

  		cout << '\n';
  	}
	
	////////////////////////////////////////////////////////////////////////print
	cout << "Map : \n";
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (map[i][j].getBlocked()) { cout << "x "; continue; }
			if (map[i][j].getPassed()) { cout << "o "; continue; }
			cout << "- ";

		}
		cout << "\n";
	}
	////////////////////////////////////////////////////////////////////////


	return 0;
}

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