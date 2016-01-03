
#include <iostream>
#include <list>
using namespace std;

struct point{
	int x = 0;
	int y = 0;
};

int g(){
	return (this.x + this.y);
}

int h(){
	return 0;
}

int f(){
	return this.g() + this.h();
}

int main(){



	//define two list
	list<point> openList;
	list<point> closeList;

	 //print the close list result out for showing professor
	cout << "The contents of way are: ";
	for (list<point>::iterator it = closeList.begin(); it != closeList.end(); it++)
    	std::cout << '( << *it.x << ',' << *it.y << ") ";

  	std::cout << '\n';

	return 0;
}
