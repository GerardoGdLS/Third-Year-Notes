/*
* File Name: square.cpp
* Assignment: Lab 2 Exercise B
* Lab section: B02
* Completed by: Gerardo Garcia de Leon
* Development Date: Sept 22, 2023
*/

#include <iostream>
#include <cmath>
#include "square.h"
using namespace std;

Square::Square(double x, double y, double side, const char* name): Shape(x, y, name)
{
	side_a = side;
}

double Square::area() const
{
	return pow(side_a, 2);
}

double Square::perimeter() const
{
	return (4*side_a);
}

double Square::get_sideA() const
{
	return side_a;
}

void Square::set_side_a(double side)
{
	side_a = side;
}

void Square::display() const
{
	cout << "Square Name: " << Shape::get_name() << endl;
	cout << "X-Coordinate: " << origin.get_x() << endl;
	cout << "Y-Coordinate: " << origin.get_y() <<endl;
	cout << "Side a: " << get_sideA() << endl;
	cout << "Area: " << area() <<endl;
	cout << "Perimeter: " << perimeter() << endl;
}

Square::Square(const Square& x): Shape(x.origin.get_x(), x.origin.get_y(), x.get_name())
{
	set_side_a(x.get_sideA());
}

Square& Square::operator =(Square& s)
{
	if(this != &s){
		Shape::operator=(s);
		set_side_a(s.get_sideA());
	}
	
	return *this;
}
