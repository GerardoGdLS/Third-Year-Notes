/*
* File Name: rectangle.cpp
* Assignment: Lab 2 Exercise B
* Lab section: B02
* Completed by: Gerardo Garcia de Leon
* Development Date: Sept 22, 2023
*/

#include <iostream>
#include "rectangle.h"
using namespace std;

Rectangle::Rectangle(double x, double y, double side1, double side2, const char* name): Square(x, y, side1, name)
{
	side_b = side2;
}

double Rectangle::get_area() const
{
	return side_b * get_sideA();
}

double Rectangle::perimeter() const
{
	return ((2*get_sideA()) + (2*side_b));
}

double Rectangle::get_sideB() const
{
	return side_b;
}

void Rectangle::set_side_b(double side)
{
	side_b = side;
}

void Rectangle::display() const
{
	cout << "Rectangle Name: " << Shape::get_name() << endl;
	cout << "X-Coordinate: " << origin.get_x() << endl;
	cout << "Y-Coordinate: " << origin.get_y() <<endl;
	cout << "Side a: " << Square::get_sideA() << endl;
	cout << "Side b: " << get_sideB() <<endl;
	cout << "Area: " << get_area() <<endl;
	cout << "Perimeter: " << perimeter() << endl;
}