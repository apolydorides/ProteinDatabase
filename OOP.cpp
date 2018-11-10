/*-------------------------------------------------------------

     Demonstration of objects and their usage with a
     custom written class Point.
     
     Course:			Programming II
     Institution: 		Department of Bioengineering
     					Imperial College London
     Author: 			James Choi
     Date written: 		1 November 2017
     Date modified: 	1 November 2017

-------------------------------------------------------------*/

#include <iostream>
#include <string>

using namespace std;

/*-------------------------------------------------------------

     class Point
     
     An object whose states are an x and y coordinate

-------------------------------------------------------------*/
class Point
{
private:
	double x;
	double y;
public:
	// constructors & destructors
	Point();
	Point(const Point &pt);
	Point(double x_in, double y_in);
	~Point();
	
	// access functions
	double get_x();
	double get_y();
	
	// operator overloading
	Point& operator =(const Point& pt_in);
	friend ostream& operator <<(ostream& os, Point pt1);
	friend Point operator +(const Point& p1, const Point& p2);
	friend Point operator -(const Point& p1, const Point& p2);
	friend Point operator -(const Point& p);
};

/* Constructors and destructors */

Point::Point()
{
	x = 0;
	y = 0;
}

Point::Point(const Point &pt_in)
{
	this->x = pt_in.x;
	this->y = pt_in.y;
}

Point::Point(double x_in, double y_in)
{
	x = x_in;
	y = y_in;
}

Point::~Point()
{

}

/* Access functions */

double Point::get_x()
{
	return x;
}

double Point::get_y()
{
	return y;
}

/* Operator overloading - members */

Point& Point::operator =(const Point& pt_in)
{	
	x = pt_in.x;
	y = pt_in.y;
	return *this;
}

/* Operator overloading - friends */

ostream& operator <<(ostream& os, Point pt1)
{	
	return os<<"("<< pt1.x <<","<< pt1.y <<")";
}

Point operator +(const Point& p1, const Point& p2)
{
	Point pt;
	pt.x = p1.x + p2.x;
	pt.y = p1.y + p2.y;
	return pt;
}

Point operator -(const Point& p1, const Point& p2)
{
	Point pt;
	pt.x = p1.x - p2.x;
	pt.y = p1.y - p2.y;
	return pt;
}

Point operator -(const Point& p)
{
	Point pt;
	pt.x = -p.x;
	pt.y = -p.y;
	return pt;
}

/*-------------------------------------------------------------

     int main()
     
     Demonstration on how to use the class Point

-------------------------------------------------------------*/
int main()
{
	Point origin;
	Point p1(1,1), p2(2,2), p3(3,3), p4;
	
	p4 = p1 + p3;
	
	cout << "The origin is " << origin << endl;
	cout << "P1 is " << p1 << endl;
	cout << "P2 is " << p2 << endl;
	cout << "P3 is " << p3 << endl;
	cout << "P4 is " << p4 << endl;
	cout << "P1 + P2 is " << p1 + p2 << endl;
	cout << "P4 - P3 is " << p4 + p3 << endl;
	cout << "-P1 is " << -p1 << endl;

	return 0;
}