/*
* File Name: graphicsWorld.cpp
* Assignment: Lab 2 Exercise B
* Lab section: B02
* Completed by: Gerardo Garcia de Leon
* Development Date: Sept 22, 2023
*/

#include <iostream>
#include "graphicsWorld.h"
using namespace std;

void GraphicsWorld::run(){
	
	#if 1 // Change 0 to 1 to test Point
	Point m (6, 8);
	Point n (6,8);
	n.set_x(9);
	cout << "\nExpected to dispaly the distance between m and n is: 3";
	cout << "\nThe distance between m and n is: " << m.distance(n);
	cout << "\nExpected second version of the distance function also print: 3";
	cout << "\nThe distance between m and n is again: "
	<< Point::distance(m, n);
	#endif // end of block to test Point

	#if 1 // Change 0 to 1 to test Square
	cout << "\n\nTesting Functions in class Square:" <<endl;
	Square s(5, 7, 12, "SQUARE - S");
	s.display();
	#endif // end of block to test Square

	#if 1 // Change 0 to 1 to test Rectangle
	cout << "\nTesting Functions in class Rectangle:" <<endl;
	Rectangle a(5, 7, 12, 15, "RECTANGLE A");
	a.display();
	Rectangle b(16 , 7, 8, 9, "RECTANGLE B");
	b.display();
	double d = a.distance(b);
	cout <<"\nDistance between square a, and b is: " << d << endl;
	Rectangle rec1 = a;
	rec1.display();
	cout << "\nTesting assignment operator in class Rectangle:" <<endl;
	Rectangle rec2 (3, 4, 11, 7, "RECTANGLE rec2");
	rec2.display();
	rec2 = a;
	a.set_side_b(200);
	a.set_side_a(100);
	cout << "\nExpected to display the following values for objec rec2: " << endl;
	cout << "Rectangle Name: RECTANGLE A\n" << "X-coordinate: 5\n" << "Y-coordinate: 7\n"
	<< "Side a: 12\n" << "Side b: 15\n" << "Area: 180\n" << "Perimeter: 54\n" ;
	cout << "\nIf it doesn't there is a problem with your assignment operator.\n" << endl;
	rec2.display();
	cout << "\nTesting copy constructor in class Rectangle:" <<endl;
	Rectangle rec3 (a);
	rec3.display();
	a.set_side_b(300);
	a.set_side_a(400);
	cout << "\nExpected to display the following values for objec rec2: " << endl;
	cout << "Rectangle Name: RECTANGLE A\n" << "X-coordinate: 5\n" << "Y-coordinate: 7\n"
	<< "Side a: 100\n" << "Side b: 200\n" << "Area: 20000\n" << "Perimeter: 600\n" ;
	cout << "\nIf it doesn't there is a problem with your assignment operator.\n" << endl;
	rec3.display();
	#endif // end of block to test Rectangle

	#if 0 // Change 0 to 1 to test using array of pointer and polymorphism
	cout << "\nTesting array of pointers and polymorphism:" <<endl;
	Shape* sh[4];
	sh[0] = &s;
	sh[1] = &b;
	sh [2] = &rec1;
	sh [3] = &rec3;
	sh [0]->display();
	sh [1]->display();
	sh [2]->display();
	sh [3]->display();
	#endif // end of block to test array of pointer and polymorphism
	
	#if 1
		cout << "\nTesting Functions in class Circle:" <<endl;
		Circle c (3, 5, 9, "CIRCLE C");
		c.display();
		cout << "the area of " << c.get_name() <<" is: "<< c.area() << endl;
		cout << "the perimeter of " << c.get_name() << " is: "<< c.perimeter() << endl;
		d = a.distance(c);
		cout << "\nThe distance between rectangle a and circle c is: " <<d <<endl;
		CurveCut rc (6, 5, 10, 12, 9, "CurveCut rc");
		rc.display();
		cout << "the area of " << rc.get_name() <<" is: "<< rc.area() <<endl;
		cout << "the perimeter of " << rc.get_name() << " is: "<< rc.perimeter() <<endl;
		d = rc.distance(c);
		cout << "\nThe distance between rc and c is: " <<d <<endl;
		// Using array of Shape pointers:
		Shape* sh[4];
		sh[0] = &s;
		sh[1] = &a;
		sh [2] = &c;
		sh [3] = &rc;
		sh [0]->display();
		cout << "\nthe area of "<< sh[0]->get_name() << "is: "<< sh[0] ->area() <<endl;
		cout << "\nthe perimeter of " << sh[0]->get_name () << " is: "<< sh[0]->perimeter() <<endl;
		sh [1]->display();
		cout << "\nthe area of "<< sh[1]->get_name() << "is: "<< sh[1] ->area() <<endl;
		cout << "\nthe perimeter of " << sh[0]->get_name () << " is: "<< sh[1]->perimeter() <<endl;
		sh [2]->display();
		cout << "\nthe area of "<< sh[2]->get_name() << "is: "<< sh[2] ->area() <<endl;
		cout << "\nthe circumference of " << sh[2]->get_name ()<< " is: "<< sh[2]->perimeter() <<endl;
		sh [3]->display();
		cout << "\nthe area of "<< sh[3]->get_name() << "is: "<< sh[3] ->area() <<endl;
		cout << "\nthe perimeter of " << sh[3]->get_name () << " is: "<< sh[3]->perimeter() <<endl;
		cout << "\nTesting copy constructor in class CurveCut:" <<endl;
		CurveCut cc = rc;
		cc.display();
		cout << "\nTesting assignment operator in class CurveCut:" <<endl;
		CurveCut cc2(2, 5, 100, 12, 9, "CurveCut cc2");
		cc2.display();
		cc2 = cc;
		cc2.display();
		
	#endif
	} // END OF FUNCTION run

int main(void)
{
	GraphicsWorld app;
	app.run();
	
	return 0;
}