
#include <iostream>
#include <list>
using namespace std;

//define a new class Point
class Point{
	private:
		int x = 0;
		int y = 0;
	public:
		Point(int a, int b){ x = a; y = b;}
		/*Point initialise(int arr[][]){

		}*/
};

/*struct point{
	int x = 0;
	int y = 0;
};*/

int g(Point p){
	return (p.x + p.y);
}

int h(Point p){
	return 0;
}

//f(x) = g(x) + h(x)
int f(Point p){
	return p.g() + p.h();
}

//find the minimun f() Point
Point min_p(list<Point> l){
	Point minP;
	int minValue;
	for (list<Point>::iterator it = l.begin(); it != l.end(); it++){
    		int temp = f(*it);
    		if( minValue < temp){
    			minValue = temp;
    			minP = *it;
    		}
    	}
    return min;
}

int main(){
	//define two list
	list<Point> openList;
	list<Point> closeList;

	 //print the close list result out for showing professor

	while(openList != NULL){

		Point tempPoint = min_p(openList);
		//add the minimun f() element into closeList
		closeList.push_back(tempPoint);
		//delete the element from openList

		cout << "The contents of way are: ";
		for (list<Point>::iterator it = closeList.begin(); it != closeList.end(); it++)
    		cout << '(' << *it.x << ',' << *it.y << ") ";

  		cout << '\n';
  	}
	return 0;
}
